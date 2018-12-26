#include "io.h"
#include <bitset>
#include <iostream>
#include "defs.h"
#include "utils.h"
void IO::printBitBoard(uint64_t bb)
{
	for (uint32_t rank = RANK_8; rank >=RANK_1; --rank)
	{
		for(uint32_t file = FILE_A; file <= FILE_H; ++file)
		{
			int sq = fileRankToSq(file, rank);
			int sq64 = BoardUtils::Sq120ToSq64[sq];

			printf("%c", ((1ULL << sq64) & bb) ? 'X' : '-' );
		}
		printf("\n");
	}
	printf("\n\n");
}

void IO::printBoard(const Board& pos){
	
	int sq,file,rank,piece;
	
	printf("\nGame Board:\n\n");
	
	for(rank = RANK_8; rank >= RANK_1; --rank) {
		printf("%d  ",rank+1);
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = fileRankToSq(file,rank);
			piece = pos.pieces[sq];
			printf("%3c",IO::PceChar[piece]);
		}
		printf("\n");
	}
	
	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; ++file) {
		printf("%3c",'a'+file);	
	}
	printf("\n");
	printf("side:%c\n",IO::SideChar[pos.side_to_move]);
	printf("enPas:%s (%d)\n",IO::epstr.at(pos.en_pas).c_str(),pos.en_pas);
	printf("castle:%c%c%c%c\n",
			pos.castle_perm & WKCA ? 'K' : '-',
			pos.castle_perm & WQCA ? 'Q' : '-',
			pos.castle_perm & BKCA ? 'k' : '-',
			pos.castle_perm & BQCA ? 'q' : '-'	
			);
	std::cout << "PosKey: " << pos.pos_key << "\n" << '\n';
}

void IO::printMoveList(const MoveList& list)
{
	for(uint32_t i = 0; i < list.size(); ++i)
	{
		Move curMove = list[i];
		printf("Move: %02d > %s (score: %d) : ",i ,curMove.toString().c_str(), curMove.score );
		std::bitset<32> bits(curMove.move);
		std::cout <<  bits <<'\n';
	}
		printf("MoveList Total: %u Moves\n\n", list.size() );
}

Move IO::parseMove(std::string input, Board& pos)
{
	stringToLower(input);

	if(input[1] < '1' || input[1] > '8') return NOMOVE;
	if(input[0] < 'a' || input[0] > 'h') return NOMOVE;
	if(input[3] < '1' || input[3] > '8') return NOMOVE;
	if(input[2] < 'a' || input[2] > 'h') return NOMOVE;

	uint32_t fromSq = fileRankToSq(input[0] - 'a', input[1] - '1');
	uint32_t toSq = fileRankToSq(input[2] - 'a', input[3] - '1');
	char promPce = input.size() > 4 ? input[4] : '*';
	MoveList m = pos.getMoveList();

	for(uint32_t i = 0; i < m.size(); ++i)
	{
		Move cur = m[i];
		if(cur.from() == fromSq && cur.to() == toSq)
		{
			if(promPce != '*')
			{
				uint32_t prom = cur.promoted();
				if(PieceInfo::PieceRookQueen[prom] && !PieceInfo::PieceBishopQueen[prom] && promPce == 'r') return cur;
				if(!PieceInfo::PieceRookQueen[prom] && PieceInfo::PieceBishopQueen[prom] && promPce == 'b') return cur;
				if(PieceInfo::PieceRookQueen[prom] && PieceInfo::PieceBishopQueen[prom] && promPce == 'q') return cur;
				if(PieceInfo::PieceKnight[prom] && promPce == 'n') return cur;
				continue;
			}
			return cur;
		}
	}
	return NOMOVE;
}

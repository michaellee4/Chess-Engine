#include "io.h"
#include <bitset>
#include <iostream>

void IOHandler::PrintBitBoard(uint64_t bb)
{
	for (uint32_t rank = RANK_8; rank >=RANK_1; --rank)
	{
		for(uint32_t file = FILE_A; file <= FILE_H; ++file)
		{
			int sq = FileRankToSq(file, rank);
			int sq64 = Sq120ToSq64[sq];

			printf("%c", ((1ULL << sq64) & bb) ? 'X' : '-' );
		}
		printf("\n");
	}
	printf("\n\n");
}

void IOHandler::PrintBoard(const Board& pos){
	
	int sq,file,rank,piece;
	
	printf("\nGame Board:\n\n");
	
	for(rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d  ",rank+1);
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = FileRankToSq(file,rank);
			piece = pos.pieces[sq];
			printf("%3c",BoardChar::PceChar[piece]);
		}
		printf("\n");
	}
	
	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; ++file) {
		printf("%3c",'a'+file);	
	}
	printf("\n");
	printf("side:%c\n",BoardChar::SideChar[pos.side_to_move]);
	printf("enPas:%s (%d)\n",BoardChar::epstr.at(pos.en_pas).c_str(),pos.en_pas);
	printf("castle:%c%c%c%c\n",
			pos.castle_perm & WKCA ? 'K' : '-',
			pos.castle_perm & WQCA ? 'Q' : '-',
			pos.castle_perm & BKCA ? 'k' : '-',
			pos.castle_perm & BQCA ? 'q' : '-'	
			);
	printf("PosKey:%lX\n\n",pos.pos_key);
}

void IOHandler::PrintMoveList(const MoveList& list)
{
	for(uint32_t i = 0; i < list.moves.size(); ++i)
	{
		Move curMove = list.moves[i];
		printf("Move: %02d > %s (score: %d) : ",i ,curMove.ToString().c_str(), curMove.score );
		std::bitset<32> bits(curMove.move);
		std::cout <<  bits <<std::endl;
	}
		printf("MoveList Total: %lu Moves\n\n", list.moves.size() );
}
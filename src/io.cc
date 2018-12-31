#include "io.h"
#include "pvtable.h"
#include "defs.h"
#include "stopwatch.h"
#include "utils.h"
#include "protocol.h"
#include "movemaker.h"
#include <bitset>
#include <iostream>
#include <sstream>

void IO::printBitBoard(uint64_t bb) noexcept
{
	for (int32_t rank = RANK_8; rank >=RANK_1; --rank)
	{
		for(uint32_t file = FILE_A; file <= FILE_H; ++file)
		{
			int sq = fileRankToSq(file, rank);
			int sq64 = BoardUtils::Sq120ToSq64[sq];
			std::cout<<(((1ULL << sq64) & bb) ? 'X' : '-' );
		}
		std::cout << '\n';
	}
	std::cout<<'\n' << std::endl;
}

void IO::printBoard(const Board& pos) noexcept
{
	int sq,file,rank,piece;
	std::cout<< "\nGame Board:\n\n";
	for(rank = RANK_8; rank >= RANK_1; --rank) {
		std::cout<<rank+1<<"  ";
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = fileRankToSq(file,rank);
			piece = pos.pieces[sq];
			printf("%3c",IO::PceChar[piece]);
		}
		std::cout<<'\n';
	}
	std::cout<<"\n   ";
	for(file = FILE_A; file <= FILE_H; ++file) {
		printf("%3c",'a'+file);	
	}
	std::cout << '\n';
	std::cout << "side:"<<IO::SideChar[pos.side_to_move]<<'\n';
	std::cout << "enPas:"<<IO::epstr.at(pos.en_pas) << " (" << pos.en_pas << ")\n";
	std::cout << "castle:"<<(pos.castle_perm & WKCA ? 'K' : '-')
						  <<(pos.castle_perm & WQCA ? 'Q' : '-')
						  <<(pos.castle_perm & BKCA ? 'k' : '-')
						  <<(pos.castle_perm & BQCA ? 'q' : '-')
						  <<'\n';
	std::cout << "PosKey: " << pos.pos_key << "\n" << '\n';
}

void IO::printMoveList(const MoveList& list) noexcept
{
	for(uint32_t i = 0; i < list.size(); ++i)
	{
		Move curMove = list[i];
		printf("Move: %02d > %s (score: %d) : ",i ,curMove.toString().c_str(), curMove.score );
		std::bitset<32> bits(curMove.move);
		std::cout <<  bits <<'\n';
	}
	std::cout << "MoveList Total: "<<list.size() << " Moves" <<"\n\n";
}

void IO::printSearchDetails(const SearchInfo& info, int32_t curDepth, int32_t bestScore, PV_Table& pv, int32_t pvMoves) noexcept
{
	std::stringstream guiStr;
	if (info.protocol == ProtocolManager::kUCI)
	{
		guiStr << "info score cp " << bestScore;
		guiStr << " depth " << curDepth;
		guiStr << " nodes " << info.nodes;
		guiStr << " time "  << Stopwatch::getTimeInMilli() - info.startTime;
	}
	else if (info.protocol == ProtocolManager::kXBoard && info.doPrint)
	{
		std::cout << curDepth << ' ' << bestScore << ' ' << (Stopwatch::getTimeInMilli() - (info.startTime / 10)) << ' ' << info.nodes;
	}
	else if (info.doPrint)
	{
		guiStr <<"score:"<<bestScore<<" depth:"<<curDepth<<" nodes:"<<info.nodes<<" time:"<<Stopwatch::getTimeInMilli()-info.startTime<<"(ms)";
	}
	if(info.protocol == ProtocolManager::kUCI || info.doPrint)
	{
		guiStr<< " pv";
		for(int i = 0; i < pvMoves; ++i)
		{
			guiStr << ' ' <<pv.pv_arr[i].toString();
		}
		guiStr<<'\n';
	}
	std::cout << guiStr.str() << std::flush;
}

void IO::printBestMove(Board& pos, const SearchInfo& info, const Move& bestMove) noexcept
{
	if(info.protocol == ProtocolManager::kUCI) 
	{
		std::cout << "bestmove " << bestMove.toString() << std::endl;
	} 
	else if(info.protocol == ProtocolManager::kXBoard)
	{		
		std::cout<<"move "<<bestMove.toString() <<std::endl;
		MM::makeMove(pos, bestMove);
	} 
	else 
	{	
		std::cout<<"\n\n***!! ChessEngine makes move "<<bestMove.toString()<<" !!***\n"<<std::endl;
		MM::makeMove(pos, bestMove);
		IO::printBoard(pos);
	}
}

Move IO::parseMove(std::string input, const Board& pos) noexcept
{
	stringToLower(input);
	if(input[1] < '1' || input[1] > '8') return NOMOVE;
	if(input[0] < 'a' || input[0] > 'h') return NOMOVE;
	if(input[3] < '1' || input[3] > '8') return NOMOVE;
	if(input[2] < 'a' || input[2] > 'h') return NOMOVE;
	uint32_t fromSq = fileRankToSq(input[0] - 'a', input[1] - '1');
	uint32_t toSq = fileRankToSq(input[2] - 'a', input[3] - '1');
	char promPce = input.size() > 4 ? input[4] : '*';
	MoveList m = pos.getAllMoves();
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

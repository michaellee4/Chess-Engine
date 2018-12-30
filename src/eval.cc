#include "eval.h"
#include "defs.h"
#include "utils.h"
#include <iostream>
using namespace BoardUtils;
int32_t Evaluator::evalPawns(const Board& pos) noexcept
{
	int32_t pce = wP;
	int32_t PnScore = 0;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		PnScore += Value::PawnTable[Sq120ToSq64[sq]];

		// Evals white isolated pawns
		if( !(EvalBB::isolatedMask[Sq120ToSq64[sq]] & pos.pawns[WHITE]) )
		{
			PnScore += Value::kIsolatedPawn;
		}

		// Evals white passed pawns
		if( !(EvalBB::whitePassedMask[Sq120ToSq64[sq]] & pos.pawns[BLACK]) )
		{
			PnScore += Value::passedPawnScore[ RankBrd[sq] ];
		}
	}	

	pce = bP;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		PnScore -= Value::PawnTable[WhiteToBlack[Sq120ToSq64[sq]]];
		
		// Evals black isolated pawns
		if( !(EvalBB::isolatedMask[Sq120ToSq64[sq]] & pos.pawns[BLACK]) )
		{
			PnScore -= Value::kIsolatedPawn;
		}

		// Evals black passed pawns
		if( !(EvalBB::blackPassedMask[Sq120ToSq64[sq]] & pos.pawns[WHITE]) )
		{
			PnScore -= Value::passedPawnScore[ 7 - RankBrd[sq] ];
		}
	}	
	return PnScore;
}

int32_t Evaluator::evalBishops(const Board& pos) noexcept
{
	int32_t pce = wB;	
	int32_t BiScore = 0;

	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		BiScore += Value::BishopTable[Sq120ToSq64[sq]];
	}	

	pce = bB;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		BiScore -= Value::BishopTable[WhiteToBlack[Sq120ToSq64[sq]]];
	}	
	return BiScore;
}

int32_t Evaluator::evalRooks(const Board& pos) noexcept
{
	int32_t pce = wR;	
	int32_t RkScore = 0;

	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		RkScore += Value::RookTable[Sq120ToSq64[sq]];

		if( !(pos.pawns[BOTH] & EvalBB::FileMask[ FileBrd[sq] ]) )
		{
			RkScore += Value::kOpenRookFile;
		}
		else if( !(pos.pawns[WHITE] & EvalBB::FileMask[ FileBrd[sq] ] ))
		{
			RkScore += Value::kSemiOpenRookFile; 
		}
	}	

	pce = bR;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		RkScore -= Value::RookTable[WhiteToBlack[Sq120ToSq64[sq]]];

		if( !(pos.pawns[BOTH] & EvalBB::FileMask[ FileBrd[sq] ]) )
		{
			RkScore -= Value::kOpenRookFile;
		}
		else if( !(pos.pawns[BLACK] & EvalBB::FileMask[ FileBrd[sq] ] ) )
		{
			RkScore -= Value::kSemiOpenRookFile; 
		}
	}	
	return RkScore;
}

int32_t Evaluator::evalQueens(const Board& pos) noexcept
{
	int32_t QnScore = 0;

	int32_t pce = wQ;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));

		if( !(pos.pawns[BOTH] & EvalBB::FileMask[ FileBrd[sq] ]) )
		{
			QnScore += Value::kOpenQueenFile;
		}
		else if( !(pos.pawns[WHITE] & EvalBB::FileMask[ FileBrd[sq] ] ) )
		{
			QnScore += Value::kSemiOpenQueenFile; 
		}
	}	

	pce = bQ;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));

		if( !(pos.pawns[BOTH] & EvalBB::FileMask[ FileBrd[sq] ]) )
		{
			QnScore -= Value::kOpenQueenFile;
		}
		else if( !(pos.pawns[BLACK] & EvalBB::FileMask[ FileBrd[sq] ] ) )
		{
			QnScore -= Value::kSemiOpenQueenFile; 
		}
	}	
	return QnScore;
}


int32_t Evaluator::evalKnights(const Board& pos) noexcept
{
	int32_t pce = wN;	
	int32_t KnScore = 0;
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		KnScore += Value::KnightTable[Sq120ToSq64[sq]];
	}	

	pce = bN;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		KnScore -= Value::KnightTable[WhiteToBlack[Sq120ToSq64[sq]]];
	}			
	return KnScore;
}


int32_t Evaluator::evaluatePosition(const Board& pos) noexcept
{
	// initial score
	int32_t score = pos.material[WHITE] - pos.material[BLACK];
	
	score += evalPawns(pos);
	score += evalKnights(pos);
	score += evalBishops(pos);	
	score += evalRooks(pos);		
	
	if(pos.side_to_move == BLACK)
	{
		score *= -1;
	}
	return score;
}

#include "eval.h"
#include "defs.h"
#include "utils.h"
int32_t Evaluator::evalPawns(const Board& pos) noexcept
{
	int32_t pce = wP;
	int32_t PnScore = 0;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		PnScore += Value::PawnTable[BoardUtils::Sq120ToSq64[sq]];
	}	

	pce = bP;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		PnScore -= Value::PawnTable[BoardUtils::WhiteToBlack[BoardUtils::Sq120ToSq64[sq]]];
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
		BiScore += Value::BishopTable[BoardUtils::Sq120ToSq64[sq]];
	}	

	pce = bB;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		BiScore -= Value::BishopTable[BoardUtils::WhiteToBlack[BoardUtils::Sq120ToSq64[sq]]];
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
		RkScore += Value::RookTable[BoardUtils::Sq120ToSq64[sq]];
	}	

	pce = bR;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		RkScore -= Value::RookTable[BoardUtils::WhiteToBlack[BoardUtils::Sq120ToSq64[sq]]];
	}	
	return RkScore;
}

int32_t Evaluator::evalKnights(const Board& pos) noexcept
{
	int32_t pce = wN;	
	int32_t KnScore = 0;
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		KnScore += Value::KnightTable[BoardUtils::Sq120ToSq64[sq]];
	}	

	pce = bN;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.sqOnBoard(sq));
		KnScore -= Value::KnightTable[BoardUtils::WhiteToBlack[BoardUtils::Sq120ToSq64[sq]]];
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

#include "search.h"
#include "stopwatch.h"
#include "stopwatch.h"

int32_t SearchAgent::evalPawns(const Board& pos)
{
	int32_t pce = wP;
	int32_t PnScore = 0;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.SqOnBoard(sq));
		PnScore += Value::PawnTable[Sq120ToSq64[sq]];
	}	

	pce = bP;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.SqOnBoard(sq));
		PnScore -= Value::PawnTable[Value::WhiteToBlack[Sq120ToSq64[sq]]];
	}	
	return PnScore;
}

int32_t SearchAgent::evalBishops(const Board& pos)
{
	int32_t pce = wB;	
	int32_t BiScore = 0;

	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.SqOnBoard(sq));
		BiScore += Value::BishopTable[Sq120ToSq64[sq]];
	}	

	pce = bB;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.SqOnBoard(sq));
		BiScore -= Value::BishopTable[Value::WhiteToBlack[Sq120ToSq64[sq]]];
	}	
	return BiScore;
}

int32_t SearchAgent::evalRooks(const Board& pos)
{
	int32_t pce = wR;	
	int32_t RkScore = 0;

	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.SqOnBoard(sq));
		RkScore += Value::RookTable[Sq120ToSq64[sq]];
	}	

	pce = bR;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.SqOnBoard(sq));
		RkScore -= Value::RookTable[Value::WhiteToBlack[Sq120ToSq64[sq]]];
	}	
	return RkScore;
}

int32_t SearchAgent::evalKnights(const Board& pos)
{
	int32_t pce = wN;	
	int32_t KnScore = 0;
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.SqOnBoard(sq));
		KnScore += Value::KnightTable[Sq120ToSq64[sq]];
	}	

	pce = bN;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
		ASSERT(pos.SqOnBoard(sq));
		KnScore -= Value::KnightTable[Value::WhiteToBlack[Sq120ToSq64[sq]]];
	}			
	return KnScore;
}


int32_t SearchAgent::evaluatePosition(const Board& pos)
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

int32_t SearchAgent::isRepetition(const Board& pos)
{
	for(int32_t idx = pos.hist_ply - pos.fifty_move; idx < pos.hist_ply - 1; ++idx)
	{
		ASSERT(idx >= 0 && (unsigned)idx < MAX_GAME_MOVES);
		if(pos.pos_key == pos.history[idx].pos_key)
			return true;
	}
	return false;
}

void SearchAgent::checkStop()
{

}

void SearchAgent::clearForSearch(Board& pos, SearchInfo& info)
{
	for(uint32_t i = 0; i < NUM_PCE_TYPES; ++i)
	{
		for(uint32_t j = 0; j < BRD_SQ_NUM; ++j)
		{
			pos.search_hist[i][j] = 0;
		}
	}

	for(uint32_t i = 0; i < NUM_SIDES; ++i)
	{
		for(uint32_t j = 0; j < MAXDEPTH; ++j)
		{
			pos.search_killers[i][j] = 0;
		}
	}

	pos.pv_table.clear();
	pos.ply = 0;

	info.startTime = Stopwatch::getTimeInMilli();
	info.stopped = false;
	info.nodes = 0;
}

int32_t SearchAgent::alphaBeta(int32_t alpha, int32_t beta, uint32_t depth, SearchInfo& info, bool doNull)
{
	return 0;
}

int32_t SearchAgent::quiescenceSearch(int32_t alpha, int32_t beta, Board& pos, SearchInfo& info)
{
	return 0;
}
	
void SearchAgent::searchPosition(Board& pos, SearchInfo& info)
{

}
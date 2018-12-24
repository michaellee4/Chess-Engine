#include "search.h"
#include "stopwatch.h"
#include <iostream>
#include "movelist.h"
#include "movemaker.h"
int32_t SearchAgent::evalPawns(const Board& pos)
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
		PnScore -= Value::PawnTable[Value::WhiteToBlack[BoardUtils::Sq120ToSq64[sq]]];
	}	
	return PnScore;
}

int32_t SearchAgent::evalBishops(const Board& pos)
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
		BiScore -= Value::BishopTable[Value::WhiteToBlack[BoardUtils::Sq120ToSq64[sq]]];
	}	
	return BiScore;
}

int32_t SearchAgent::evalRooks(const Board& pos)
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
		RkScore -= Value::RookTable[Value::WhiteToBlack[BoardUtils::Sq120ToSq64[sq]]];
	}	
	return RkScore;
}

int32_t SearchAgent::evalKnights(const Board& pos)
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
		KnScore -= Value::KnightTable[Value::WhiteToBlack[BoardUtils::Sq120ToSq64[sq]]];
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
	info.fh = 0;
	info.fhf = 0;
}

int32_t SearchAgent::alphaBeta(int32_t alpha, int32_t beta, uint32_t depth, Board& pos, SearchInfo& info, bool doNull)
{
    ASSERT(checkBoard(pos)); 

    ++info.nodes;
	if(depth == 0) {
        return this->evaluatePosition(pos);
    }

    if(isRepetition(pos) || pos.fifty_move >= 100)
    {
    	return 0;
    }
    if((unsigned)pos.ply > MAXDEPTH - 1)
    {
    	return this->evaluatePosition(pos);
    }

    MoveList m;
    m.generateAllMoves(pos);
    int32_t legalMoves = 0;
    int32_t prevAlpha = alpha;
    Move bestMove = noMove;
    int score = -INFINITY;

	for(uint32_t MoveNum = 0; MoveNum < m.size(); ++MoveNum) {	
        if ( !MM::makeMove(pos,m[MoveNum]))  {
            continue;
        }
        ++legalMoves;
        score = -1 * this->alphaBeta(-beta, -alpha, depth - 1, pos, info, true);
        MM::takeMove(pos);
        if(score > alpha)
        {
        	if(score >= beta)
        	{
        		if(legalMoves == 1)
        		{
        			++info.fhf;
        		}
        		++info.fh;
        		return beta;
        	}
        	alpha = score;
        	bestMove = m[MoveNum];
        }
    }
    if(legalMoves == 0)
    {
    	if(pos.sqAttacked(pos.king_sq[pos.side_to_move], !pos.side_to_move))
    	{
    		return -MATE + pos.ply;
    	}
    	else return 0;
    }

    if(alpha != prevAlpha)
    {
    	pos.pv_table.insert(pos, bestMove);
    }
	return alpha;
}

int32_t SearchAgent::quiescenceSearch(int32_t alpha, int32_t beta, Board& pos, SearchInfo& info)
{
	return 0;
}

//uses iterative deepening
void SearchAgent::searchPosition(Board& pos, SearchInfo& info)
{
	using std::cout;
	using std::endl;
	Move bestMove = noMove;
	int32_t bestScore = -INFINITY;
	this->clearForSearch(pos, info);

	for(uint32_t curDepth = 1 ; curDepth <= info.depth; ++curDepth)
	{
		bestScore = this->alphaBeta(-INFINITY, INFINITY, curDepth, pos, info, true);

		// check time
		int32_t pvMoves = PV_Table::getPvLine(pos, curDepth);
		bestMove = pos.pv_arr[0];
		cout<<"Depth:" << curDepth << " score:" << bestScore << " move:" << bestMove.toString() << " nodes:" << info.nodes<<endl;
		
		pvMoves = PV_Table::getPvLine(pos, curDepth);
		cout<< "PvLine of " << pvMoves << " Moves: ";
		for(int i = 0; i < pvMoves; ++i)
		{
			Move move = pos.pv_arr[i];
			cout << move.toString() << " ";
		}
		cout<<endl;
		cout << "Ordering: " << info.fhf/info.fh << "\n" << endl;
	}
}

#include "search.h"
#include "stopwatch.h"
#include "movelist.h"
#include "utils.h"
#include "movemaker.h"
#include "io.h"
#include <sstream>
#include <iostream>
#include <cstdio>
SearchAgent::SearchAgent() noexcept : eval() {}

bool SearchAgent::threeFoldRepetition(const Board& pos) noexcept
{
	int32_t numRep = 0;
	for(int32_t i = 0; i < pos.hist_ply; ++i)
	{
		if(pos.history[i].pos_key == pos.pos_key)
		{
			++numRep;
		}
	}
	return numRep > 2;
}

bool SearchAgent::drawnMaterial(const Board& pos) noexcept
{
	auto pieceList = pos.piece_list;
	if(!pieceList[wP].empty() || !pieceList[bP].empty()) return false;
	if(!pieceList[wQ].empty() || !pieceList[bQ].empty()) return false;
	if(!pieceList[wR].empty() || !pieceList[bR].empty()) return false;
	if(pieceList[wB].size() > 1 || pieceList[bB].size() > 1) return false;
	if(pieceList[wN].size() > 1 || pieceList[bN].size() > 1) return false;
	if(!pieceList[wN].empty() && !pieceList[wB].empty()) return false;
	if(!pieceList[bN].empty() && !pieceList[bB].empty()) return false;
	return true;
}

int32_t SearchAgent::isRepetition(const Board& pos) noexcept
{
	for(int32_t idx = pos.hist_ply - pos.fifty_move; idx < pos.hist_ply - 1; ++idx)
	{
		ASSERT(idx >= 0 && (unsigned)idx < MAX_GAME_MOVES);
		if(pos.pos_key == pos.history[idx].pos_key)
			return true;
	}
	return false;
}

bool SearchAgent::inCheck(const Board& pos) noexcept
{
	return pos.sqAttacked(pos.king_sq[pos.side_to_move], !pos.side_to_move);
}

bool SearchAgent::isGameOver(Board& pos) noexcept
{
	if(pos.fifty_move > 100)
	{
		std::cout << "1/2-1/2 {fifty move rule (claimed by " << NAME << ")}" << std::endl;
		return true;
	}
	if(threeFoldRepetition(pos))
	{
		std::cout << "1/2-1/2 {3-fold repetition (claimed by " << NAME << ")}" << std::endl;
		return true;
	}
	if(drawnMaterial(pos))
	{
		std::cout << "1/2-1/2 {insufficient material (claimed by " << NAME << ")}" << std::endl;
		return true;
	}

	MoveList m = pos.getAllMoves();
	bool legalMoveFound = false;
	for(uint32_t i = 0; i < m.size(); ++i)
	{
		Move curMove = m[i];
		if(!MM::makeMove(pos, curMove))
		{
			continue;
		}
		legalMoveFound = true;
		MM::takeMove(pos);
		break;
	}
	if(legalMoveFound) return false;

	if(inCheck(pos))
	{
		if(pos.side_to_move == WHITE)
		{
			std::cout << "0-1 {black mates (claimed by "<< NAME<< ")}" << std::endl;
			return true;			
		}
		else
		{
			std::cout << "0-1 {white mates (claimed by "<< NAME<< ")}" << std::endl;
			return true;
		}
	}
	else
	{
			std::cout << "\n1/2-1/2 {stalemate (claimed by "<< NAME<< ")}" << std::endl;
			return true;
	}
	return false;
}

void SearchAgent::checkStop(SearchInfo& info)
{
	if(info.timeLimit && Stopwatch::getTimeInMilli() > info.stopTime)
	{
		info.stopped = true;
	}
	ReadInput(info);
}

void SearchAgent::clearForSearch(Board& pos, SearchInfo& info) noexcept
{
	for(uint32_t i = 0; i < PCE_TYPES; ++i)
	{
		for(uint32_t j = 0; j < BRD_ARR_SIZE; ++j)
		{
			pos.search_hist[i][j] = 0;
		}
	}

	for(uint32_t i = 0; i < NUM_SIDES; ++i)
	{
		for(uint32_t j = 0; j < MAX_DEPTH; ++j)
		{
			pos.search_killers[i][j] = NOMOVE;
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

int32_t SearchAgent::alphaBeta(int32_t alpha, int32_t beta, uint32_t depth, Board& pos, SearchInfo& info, bool doNull) noexcept
{
	(void)doNull;
    ASSERT(checkBoard(pos)); 

	if(depth == 0) {
		return this->quiescenceSearch(alpha, beta, pos, info);
    }

	if((info.nodes & CHECK_TIMER )== 0)
	{
		this->checkStop(info);
	}

    ++info.nodes;

    if((isRepetition(pos) || pos.fifty_move >= 100) && pos.ply)
    {
    	return 0;
    }
    if((unsigned)pos.ply > MAX_DEPTH - 1)
    {
    	return eval.evaluatePosition(pos);
    }
    if(inCheck(pos))
    {
    	depth ++;
    }

    MoveList m = pos.getAllMoves();
    int32_t legalMoves = 0;
    int32_t prevAlpha = alpha;
    Move bestMove = NOMOVE;
    int score = -Value::INFINITY;
    Move pvMove = pos.pv_table.get(pos);
    if(pvMove != NOMOVE)
    {
		for(uint32_t moveNum = 0; moveNum < m.size(); ++moveNum) 
		{
			if(m[moveNum] == pvMove)
			{
				m[moveNum].score = m.PVMOVE_OFFSET;
				break;
			}
		}
    }

	for(uint32_t moveNum = 0; moveNum < m.size(); ++moveNum) 
	{
		m.reorderList(moveNum);
        Move curMove = m[moveNum];

        if ( !MM::makeMove(pos,curMove))  {
            continue;
        }
        ++legalMoves;
        score = -1 * this->alphaBeta(-beta, -alpha, depth - 1, pos, info, true);
        MM::takeMove(pos);
        if(info.stopped)
        {
        	return 0;
        }   
        if(score > alpha)
        {
        	if(score >= beta)
        	{
        		if(legalMoves == 1)
        		{
        			++info.fhf;
        		}
        		++info.fh;

        		if(!curMove.wasCapture())
        		{
        			pos.search_killers[1][pos.ply] = pos.search_killers[0][pos.ply];
        			pos.search_killers[0][pos.ply] = curMove;
        		}

        		return beta;
        	}
        	alpha = score;
        	bestMove = curMove;
        	if(!curMove.wasCapture())
        	{
        		pos.search_hist[pos.pieces[bestMove.from()]][bestMove.to()] += depth;
        	}
        }
    }
    if(legalMoves == 0)
    {
    	if(pos.sqAttacked(pos.king_sq[pos.side_to_move], !pos.side_to_move))
    	{
    		return -Value::MATE + pos.ply;
    	}
    	else return 0;
    }

    if(alpha != prevAlpha)
    {
    	pos.pv_table.insert(pos, bestMove);
    }
	return alpha;
}

int32_t SearchAgent::quiescenceSearch(int32_t alpha, int32_t beta, Board& pos, SearchInfo& info) noexcept
{
	ASSERT(checkBoard(pos));

	if( ( info.nodes & CHECK_TIMER )== 0)
	{
		this->checkStop(info);
	}

	++info.nodes;

	if(isRepetition(pos) || pos.fifty_move >= 100)
	{
		return 0;
	}
	if((unsigned)pos.ply > MAX_DEPTH - 1)
	{
		return eval.evaluatePosition(pos);
	}

	int32_t initialScore = eval.evaluatePosition(pos);
	
	if(initialScore >= beta)
	{
		return beta;
	}
	else if(initialScore > alpha)
	{
		alpha = initialScore;
	}

	MoveList m = pos.getAllCaptureMoves();

    int32_t legalMoves = 0;
    int32_t prevAlpha = alpha;
    Move bestMove = NOMOVE;
    int score = -Value::INFINITY;

    for(uint32_t moveNum = 0; moveNum < m.size(); ++moveNum) 
	{
		m.reorderList(moveNum);
        Move curMove = m[moveNum];

        if ( !MM::makeMove(pos,curMove))  {
            continue;
        }
        ++legalMoves;
        score = -1 * this->quiescenceSearch(-beta, -alpha, pos, info);
        MM::takeMove(pos);
        if(info.stopped)
        {
        	return 0;
        }
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
        	bestMove = curMove;
        }
    }
	if(alpha != prevAlpha)
	{
		pos.pv_table.insert(pos, bestMove);
	}
	return alpha;
}

//uses iterative deepening
void SearchAgent::searchPosition(Board& pos, SearchInfo& info) noexcept
{
	//use a string stream to build up gui string
	Move bestMove = NOMOVE;
	int32_t bestScore = -Value::INFINITY;
	this->clearForSearch(pos, info);

	for(uint32_t curDepth = 1 ; curDepth <= info.depth; ++curDepth)
	{
		std::stringstream guiStr;
		bestScore = this->alphaBeta(-Value::INFINITY, Value::INFINITY, curDepth, pos, info, true);
		if(info.stopped)
		{
			break;
		}
		bestMove = pos.pv_arr[0];
		PV_Table::getPvLine(pos, curDepth);
		IO::printSearchDetails(pos, info, curDepth, bestScore);
	}
	IO::printBestMove(pos, info, bestMove);
}

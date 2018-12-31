#include "eval.h"
#include "defs.h"
#include "utils.h"
#include <iostream>
#include <cmath>
using namespace BoardUtils;
int32_t Evaluator::evalPawns(const Board& pos) noexcept
{
	int32_t pce = wP;
	int32_t PnScore = 0;	
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
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
	for(int32_t sq : pos.piece_list[pce]) {
			BiScore += Value::BishopTable[Sq120ToSq64[sq]];
	}	
	pce = bB;	
	for(int32_t sq : pos.piece_list[pce]) {
			BiScore -= Value::BishopTable[WhiteToBlack[Sq120ToSq64[sq]]];
	}	
	if(pos.piece_list[wB].size() >= 2) BiScore += Value::kBishopPair;
	if(pos.piece_list[bB].size() >= 2) BiScore -= Value::kBishopPair;
	return BiScore;
}
int32_t Evaluator::evalRooks(const Board& pos) noexcept
{
	int32_t pce = wR;	
	int32_t RkScore = 0;
	for(uint32_t pceNum = 0; pceNum < pos.piece_list[pce].size(); ++pceNum) {
		int32_t sq = pos.piece_list[pce][pceNum];
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
int32_t Evaluator::evalKings(const Board& pos) noexcept
{
	int32_t KingScore = 0;
	int32_t pce = wK;
	// use king sq?
	int32_t sq = pos.piece_list[pce][0];
	if(pos.material[BLACK] <= Value::kEndGameThreshold)
	{
		KingScore += Value::KingEndGame[ Sq120ToSq64[sq] ];
	}
	else
	{
		KingScore += Value::KingOpening[ Sq120ToSq64[sq] ];	
	}
	pce = bK;
	sq = pos.piece_list[pce][0];
	if(pos.material[WHITE] <= Value::kEndGameThreshold)
	{
		KingScore -= Value::KingEndGame[ WhiteToBlack[ Sq120ToSq64[sq]] ];
	}
	else
	{
		KingScore -= Value::KingOpening[ WhiteToBlack[ Sq120ToSq64[sq]] ];	
	}
	return KingScore;
}
int32_t Evaluator::evalKnights(const Board& pos) noexcept
{
	int32_t pce = wN;	
	int32_t KnScore = 0;
	for(int32_t sq : pos.piece_list[pce]) {
			KnScore += Value::KnightTable[Sq120ToSq64[sq]];
	}	
	pce = bN;	
	for(int32_t sq : pos.piece_list[pce]) {
			KnScore -= Value::KnightTable[WhiteToBlack[Sq120ToSq64[sq]]];
	}			
	return KnScore;
}
// Drawn material based on optimal play, Credits to the sjeng 11.2 engine
bool Evaluator::drawnMaterial(const Board& pos) noexcept
{
    if (!pos.piece_list[wR].size() && !pos.piece_list[bR].size() && !pos.piece_list[wQ].size() && !pos.piece_list[bQ].size()) 
    {
	  	if (!pos.piece_list[bB].size() && !pos.piece_list[wB].size()) 
	  	{
	      	if (pos.piece_list[wN].size() < 3 && pos.piece_list[bN].size() < 3) 
	      	{  
	      		return true; 
	    	}
	  	} 
	  	else if (!pos.piece_list[wN].size() && !pos.piece_list[bN].size()) 
	  	{
	  		int32_t wBsize = pos.piece_list[wB].size();
	  		int32_t bBsize = pos.piece_list[bB].size();
	    	if (std::abs(wBsize - bBsize) < 2) 
	    	{ 
	     		return true; 
	    	}
	  	} 
	  	else if ((pos.piece_list[wN].size() < 3 && !pos.piece_list[wB].size()) || (pos.piece_list[wB].size() == 1 && !pos.piece_list[wN].size())) 
	  	{
	    	if ((pos.piece_list[bN].size() < 3 && !pos.piece_list[bB].size()) || (pos.piece_list[bB].size() == 1 && !pos.piece_list[bN].size()))  
	    	{
	    		return true; 
	    	}
	  	}
	} 
	else if (!pos.piece_list[wQ].size() && !pos.piece_list[bQ].size()) 
	{
        if (pos.piece_list[wR].size() == 1 && pos.piece_list[bR].size() == 1) 
        {
            if ((pos.piece_list[wN].size() + pos.piece_list[wB].size()) < 2 && (pos.piece_list[bN].size() + pos.piece_list[bB].size()) < 2)	
            	{
            		return true; 
            	}
        } 
        else if (pos.piece_list[wR].size() == 1 && !pos.piece_list[bR].size()) 
        {
            if ((pos.piece_list[wN].size() + pos.piece_list[wB].size() == 0) && (((pos.piece_list[bN].size() + pos.piece_list[bB].size()) == 1) || ((pos.piece_list[bN].size() + pos.piece_list[bB].size()) == 2))) 
            	{
            		return true; 
            	}
        } 
        else if (pos.piece_list[bR].size() == 1 && !pos.piece_list[wR].size()) 
        {
            if ((pos.piece_list[bN].size() + pos.piece_list[bB].size() == 0) && (((pos.piece_list[wN].size() + pos.piece_list[wB].size()) == 1) || ((pos.piece_list[wN].size() + pos.piece_list[wB].size()) == 2))) 
           	{
           		return true; 
            }
        }
    }
  	return false;
}
int32_t Evaluator::evaluatePosition(const Board& pos) noexcept
{
	if((pos.piece_list[wP].size() == 0 && pos.piece_list[bP].size() == 0) && drawnMaterial(pos))
	{
		return 0;
	}
	// initial score
	int32_t score = pos.material[WHITE] - pos.material[BLACK];
	score += evalPawns(pos);
	score += evalKnights(pos);
	score += evalBishops(pos);	
	score += evalRooks(pos);
	score += evalQueens(pos);
	score += evalKings(pos);		
	if(pos.side_to_move == BLACK)
	{
		score *= -1;
	}
	return score;
}

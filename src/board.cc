#include "board.h"
#include "defs.h"

void Board::ResetBoard(void)
{
	for(int i = 0; i < BRD_SQ_NUM; i ++)
	{
		this->pieces[i] = NO_SQ;
	}

	for(int i = 0; i < 64; i ++)
	{
		this->pieces[Sq64ToSq120[i]] = EMPTY;
	}

	for(int i = 0; i < 3; i ++)
	{
		this->big_pce[i] = 0;
		this->maj_pce[i] = 0;
		this->min_pce[i] = 0;
		this->pawns[i] = 0;
	}

	for(int i = 0; i < 13; i ++)
	{
		this->piece_num[i] = 0;
	}

	this->king_sq[0] = 0;
	this->king_sq[1] = 0;

	this->side_to_move = BOTH;
	this->en_pas = NO_SQ;
	this->fifty_move = 0;

	this->castle_perm = 0;
	this->ply = 0;
	this->hist_ply = 0;

	this->pos_key = 0ULL;
}
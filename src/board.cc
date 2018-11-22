#include "board.h"
#include "defs.h"
#include "debug.h"
#include "hash.h"
#include "utils.h"
#include "bitboard.h"
#include <string>
#include <sstream>
#include <cstdio> 

Board::Board():pawns(3), 
			   king_sq(2), 
			   piece_num(13), 
			   piece_list(13, std::vector<int>()),
			   big_pce(2), 
			   maj_pce(2), 
			   min_pce(2), 
			   material(2), 
			   history(MAX_GAME_MOVES)
{
	for(int i = 0; i < 13; i++)
	{
		this->piece_list[i].reserve(10);
	}
	this->ParseFEN(START_FEN);
}

Board::Board(const std::string fen):pawns(3), 
									king_sq(2), 
									piece_num(13), 
			   						piece_list(13, std::vector<int>()),
									big_pce(2),
									maj_pce(2), 
									min_pce(2), 
									material(2), 
									history(MAX_GAME_MOVES) 
{
	for(int i = 0; i < 13; i++)
	{
		this->piece_list[i].reserve(10);
	}
	this->ParseFEN(fen);
}

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

	for(int i = 0; i < 2; i ++)
	{
		this->big_pce[i] = 0;
		this->maj_pce[i] = 0;
		this->min_pce[i] = 0;
		this->material[i] = 0;
		this->pawns[i] = 0;
	}
	this->pawns[2] = 0;

	for(int i = 0; i < 13; i ++)
	{
		this->piece_list[i].clear();
	}

	this->king_sq[WHITE] = 0;
	this->king_sq[BLACK] = 0;

	this->side_to_move = BOTH;
	this->en_pas = NO_SQ;
	this->fifty_move = 0;

	this->castle_perm = 0;
	this->ply = 0;
	this->hist_ply = 0;

	this->pos_key = 0ULL;
}

void Board::ParseFEN(const std::string fen)
{
	using namespace std;
	this->ResetBoard();

	std::istringstream stream(fen);
	std::string section;
	// piece locations fix this
	std::getline(stream, section, ' ');
	//cout << section << endl;
	int fenIdx = 0;
	for(int rank = RANK_8; rank >= RANK_1; rank --)
	{
		for(int file = FILE_A; file <= FILE_H; file++)
		{
			if(isdigit(section[fenIdx]))
			{
				for(int i = 0; i < section[fenIdx] - '0'; i++)
				{
					this->pieces[FileRankToSq(file, rank)] = EMPTY;
					file++;
				}
				file--;

			}
			else
			{
				switch(section[fenIdx])
				{
					case 'p':this->pieces[FileRankToSq(file, rank)] = bP;break;
					case 'n':this->pieces[FileRankToSq(file, rank)] = bN;break;
					case 'b':this->pieces[FileRankToSq(file, rank)] = bB;break;
					case 'r':this->pieces[FileRankToSq(file, rank)] = bR;break;
					case 'q':this->pieces[FileRankToSq(file, rank)] = bQ;break;
					case 'k':this->pieces[FileRankToSq(file, rank)] = bK;break;
					case 'P':this->pieces[FileRankToSq(file, rank)] = wP;break;
					case 'N':this->pieces[FileRankToSq(file, rank)] = wN;break;
					case 'B':this->pieces[FileRankToSq(file, rank)] = wB;break;
					case 'R':this->pieces[FileRankToSq(file, rank)] = wR;break;
					case 'Q':this->pieces[FileRankToSq(file, rank)] = wQ;break;
					case 'K':this->pieces[FileRankToSq(file, rank)] = wK;break;
				}
			}
			fenIdx++;
		}
		fenIdx++;
	}

	// side to move
	std::getline(stream, section, ' ');
	this->side_to_move = section[0] == 'w' ? WHITE : BLACK;

	// Castling permissions
	std::getline(stream, section, ' ');
	this->castle_perm = 0;
	if(section[0] != '-')
	{
		for(int i = 0; i < section.size(); i ++)
		{
			switch(section[i])
			{
				case 'K':
					this->castle_perm |= WKCA;
					break;
				case 'Q':
					this->castle_perm |= WQCA;
					break;
				case 'k':
					this->castle_perm |= BKCA;
					break;
				case 'q':
					this->castle_perm |= BQCA;
					break;
			}
		}
	}

	// En Passant Square
	std::getline(stream, section, ' ');
	if(section != "-")
	{
		int file = section[0] - 'a';
		int rank = section[1] - '1';
		this->en_pas = FileRankToSq(file, rank);
	}
	// halfmove clock (halfmoves since capture or pawn advance)
	std::getline(stream, section, ' ');
	if(stream.good())
	{
		this->fifty_move = stoi(section);
		// fullmove counter
		std::getline(stream, section, ' ');
		this->hist_ply = (stoi(section) - 1 ) * 2 + (this->side_to_move);
	}
	else
	{
		this->fifty_move = 0;
		this->hist_ply = 1;
	}
	this->pos_key = Hash::GeneratePosKey(*this);
	this->UpdatePieceLists();
}

void Board::PrintBoard() const{
	
	int sq,file,rank,piece;
	
	printf("\nGame Board:\n\n");
	
	for(rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d  ",rank+1);
		for(file = FILE_A; file <= FILE_H; file++) {
			sq = FileRankToSq(file,rank);
			piece = this->pieces[sq];
			printf("%3c",BoardChar::PceChar[piece]);
		}
		printf("\n");
	}
	
	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; file++) {
		printf("%3c",'a'+file);	
	}
	printf("\n");
	printf("side:%c\n",BoardChar::SideChar[this->side_to_move]);
	printf("enPas:%s (%d)\n",BoardChar::epstr.at(this->en_pas).c_str(),this->en_pas);
	printf("castle:%c%c%c%c\n",
			this->castle_perm & WKCA ? 'K' : '-',
			this->castle_perm & WQCA ? 'Q' : '-',
			this->castle_perm & BKCA ? 'k' : '-',
			this->castle_perm & BQCA ? 'q' : '-'	
			);
	printf("PosKey:%llX\n\n",this->pos_key);
}

void Board::UpdatePieceLists()
{
	for (int index = 0; index < BRD_SQ_NUM; index ++)
	{
		int piece = this->pieces[index];
		// on board
		if( IsPiece(piece) )
		{
			int color = PieceInfo::PieceCol[piece];
			this->big_pce[color] += PieceInfo::PieceBig[piece];
			this->maj_pce[color] += PieceInfo::PieceMaj[piece];
			this->min_pce[color] += PieceInfo::PieceMin[piece];
			this->material[color] += PieceInfo::PieceVal[piece];

			// this->piece_list[piece][this->piece_num[piece]] = index;
			// this->piece_num[piece]++;
			this->piece_list[piece].push_back(index);

			if(piece == wK) this->king_sq[WHITE] = index;
			if(piece == bK) this->king_sq[BLACK] = index;

			if(piece == wP) 
			{
				BB::SetBit(this->pawns[WHITE], Sq120ToSq64[index]);
				BB::SetBit(this->pawns[BOTH], Sq120ToSq64[index]);
			}
			if(piece == bP) 
			{
				BB::SetBit(this->pawns[BLACK], Sq120ToSq64[index]);
				BB::SetBit(this->pawns[BOTH], Sq120ToSq64[index]);
			}
		}
	}
}

bool CheckBoard(const Board& pos)
{
	int t_pceNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int t_bigPce[2] = { 0, 0};
	int t_majPce[2] = { 0, 0};
	int t_minPce[2] = { 0, 0};
	int t_material[2] = { 0, 0};
	
	int sq64,t_piece,t_pce_num,sq120,colour,pcount;
	
	U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};
	
	t_pawns[WHITE] = pos.pawns[WHITE];
	t_pawns[BLACK] = pos.pawns[BLACK];
	t_pawns[BOTH] = pos.pawns[BOTH];
	
	// check piece lists
	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		for(t_pce_num = 0; t_pce_num < pos.piece_list[t_piece].size(); ++t_pce_num) {
			sq120 = pos.piece_list[t_piece][t_pce_num];
			ASSERT(pos.pieces[sq120]==t_piece);
		}	
	}
	
	// check piece count and other counters	
	for(sq64 = 0; sq64 < 64; ++sq64) {
		sq120 = Sq64ToSq120[sq64];
		t_piece = pos.pieces[sq120];
		t_pceNum[t_piece]++;
		colour = PieceInfo::PieceCol[t_piece];
		if( PieceInfo::PieceBig[t_piece] == true) t_bigPce[colour]++;
		if( PieceInfo::PieceMin[t_piece] == true) t_minPce[colour]++;
		if( PieceInfo::PieceMaj[t_piece] == true) t_majPce[colour]++;
		
		t_material[colour] += PieceInfo::PieceVal[t_piece];
	}
	
	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		ASSERT(t_pceNum[t_piece]==pos.piece_list[t_piece].size());	
	}
	
	// check bitboards count
	pcount = BB::CountBits(t_pawns[WHITE]);
	ASSERT(pcount == pos.piece_list[wP].size());
	pcount = BB::CountBits(t_pawns[BLACK]);
	ASSERT(pcount == pos.piece_list[bP].size());
	pcount = BB::CountBits(t_pawns[BOTH]);
	ASSERT(pcount == (pos.piece_list[bP].size() + pos.piece_list[wP].size()));
	
	// check bitboards squares
	while(t_pawns[WHITE]) {
		sq64 = BB::PopBit(t_pawns[WHITE]);
		ASSERT(pos.pieces[Sq64ToSq120[sq64]] == wP);
	}
	
	while(t_pawns[BLACK]) {
		sq64 = BB::PopBit(t_pawns[BLACK]);
		ASSERT(pos.pieces[Sq64ToSq120[sq64]] == bP);
	}
	
	while(t_pawns[BOTH]) {
		sq64 = BB::PopBit(t_pawns[BOTH]);
		ASSERT( (pos.pieces[Sq64ToSq120[sq64]] == bP) || (pos.pieces[Sq64ToSq120[sq64]] == wP) );
	}
	
	ASSERT(t_material[WHITE]==pos.material[WHITE] && t_material[BLACK]==pos.material[BLACK]);
	ASSERT(t_minPce[WHITE]==pos.min_pce[WHITE] && t_minPce[BLACK]==pos.min_pce[BLACK]);
	ASSERT(t_majPce[WHITE]==pos.maj_pce[WHITE] && t_majPce[BLACK]==pos.maj_pce[BLACK]);
	ASSERT(t_bigPce[WHITE]==pos.big_pce[WHITE] && t_bigPce[BLACK]==pos.big_pce[BLACK]);	
	
	ASSERT(pos.side_to_move==WHITE || pos.side_to_move==BLACK);
	// printf("%d %d\n",Hash::GeneratePosKey(pos), pos.pos_key );ASSERT(Hasher::GeneratePosKey(pos)==pos.pos_key);
	
	ASSERT(pos.en_pas==NO_SQ || ( RankBrd[pos.en_pas]==RANK_6 && pos.side_to_move == WHITE)
		 || ( RankBrd[pos.en_pas]==RANK_3 && pos.side_to_move == BLACK));
	
	ASSERT(pos.pieces[pos.king_sq[WHITE]] == wK);
	ASSERT(pos.pieces[pos.king_sq[BLACK]] == bK);
		 
	return true;
}


bool Board::SqOnBoard(int sq) const
{
	return !(this->pieces[sq] == OFFBOARD);
}

int Board::SqAttacked(const int sq, const int attacker) const
{
	int numAttackers = 0;

	// Check Pawn
	if(attacker == WHITE)
	{
		if(this->pieces[sq - 11] == wP)
			numAttackers++;
		if(this->pieces[sq - 9] == wP)
			numAttackers++;
	}
	else
	{
		if(this->pieces[sq + 11] == bP)
			numAttackers++;
		if(this->pieces[sq + 9] == bP)
			numAttackers++;
	}



	// Check Knight
	int attackingKnight = attacker == WHITE ? wN : bN;
	for(int i = 0; i < 8; i++)
	{
		if(this->pieces[sq + Attack::KnMoves[i]] == attackingKnight)
			numAttackers++;
	}

	// Check Horizontal and Vertical
	int attackingRook = attacker == WHITE ? wR : bR;
	int attackingQueen = attacker == WHITE ? wQ : bQ;
	for(int i = 0 ; i < 4; i ++)
	{
		int move = Attack::RkMoves[i];
		int t_sq = sq + move;
		int pce = this->pieces[t_sq];
		while(pce != OFFBOARD)
		{
			if(pce != EMPTY)
			{
				if(pce == attackingRook || pce == attackingQueen)
					numAttackers++;
				break;
			}
			t_sq += move;
			pce = this->pieces[t_sq];
		}

	}

	int attackingBishop = attacker == WHITE ? wB : bB;
	for(int i = 0 ; i < 4; i ++)
	{
		int move = Attack::BiMoves[i];
		int t_sq = sq + move;
		int pce = this->pieces[t_sq];
		while(pce != OFFBOARD)
		{
			if(pce != EMPTY)
			{
				if(pce == attackingBishop || pce == attackingQueen)
					numAttackers++;
				break;
			}
			t_sq += move;
			pce = this->pieces[t_sq];
		}
	}

	int attackingKing = attacker == WHITE ? wK : bK;
	for(int i = 0; i < 8; i++)
	{
		if(this->pieces[sq + Attack::KiMoves[i]] == attackingKing)
			numAttackers++;
	}
	// Check Diagonals

	return numAttackers;
}



void Board::PrintMoveList() const
{

}

void Board::GenerateAllMoves()
{

}
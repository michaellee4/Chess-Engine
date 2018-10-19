#include "board.h"
#include "defs.h"
#include "debug.h"
#include <string>
#include <sstream>
#include "hash.h"
#include "utils.h"
#include <cstdio>
#include <unordered_map>

char PceChar[] = ".PNBRQKpnbrqk";
char SideChar[] = "wb-";
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";
std::unordered_map<int, std::string> epstr = {{71,"a6"}, {72,"b6"}, {73,"c6"}, {74,"d6"}, {75,"e6"}, {76,"f6"}, {77,"g6"}, {78,"h6"},
										 {41,"a3"}, {42,"b3"}, {43,"c3"}, {44,"d3"}, {45,"e3"}, {46,"f3"}, {47,"g3"}, {48,"h3"}};

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

void Board::ParseFEN(std::string fen)
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
	this->fifty_move = stoi(section);

	// fullmove counter
	std::getline(stream, section, ' ');
	this->hist_ply = stoi(section) * 2 + (this->side_to_move);

	this->pos_key = GeneratePosKey(*this);
}

void Board::PrintBoard() {
	
	int sq,file,rank,piece;
	
	printf("\nGame Board:\n\n");
	
	for(rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d  ",rank+1);
		for(file = FILE_A; file <= FILE_H; file++) {
			sq = FileRankToSq(file,rank);
			piece = this->pieces[sq];
			printf("%3c",PceChar[piece]);
		}
		printf("\n");
	}
	
	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; file++) {
		printf("%3c",'a'+file);	
	}
	printf("\n");
	printf("side:%c\n",SideChar[this->side_to_move]);
	printf("enPas:%s (%d)\n",epstr[this->en_pas].c_str(),this->en_pas);
	printf("castle:%c%c%c%c\n",
			this->castle_perm & WKCA ? 'K' : '-',
			this->castle_perm & WQCA ? 'Q' : '-',
			this->castle_perm & BKCA ? 'k' : '-',
			this->castle_perm & BQCA ? 'q' : '-'	
			);
	printf("PosKey:%llX\n",this->pos_key);
}
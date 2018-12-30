#include "board.h"
#include "defs.h"
#include "debug.h"
#include "hash.h"
#include "utils.h"
#include "bitboard.h"
#include "movelist.h"
#include <string>
#include <sstream>
#include <cstdio> 

Board::Board() noexcept :
			   pieces(kBoardArraySize),
			   pawns(3), 
			   king_sq(kNumPlayers),
			   side_to_move(WHITE),
			   en_pas(NO_SQ),
			   fifty_move(0),
			   ply(0),
			   hist_ply(0),
			   pos_key(0),
			   castle_perm(0xf),
			   piece_list(kNumPceTypes, std::vector<uint32_t>()),
			   big_pce(kNumPlayers), 
			   maj_pce(kNumPlayers), 
			   min_pce(kNumPlayers), 
			   material(kNumPlayers), 
			   history(kMoveLimit),
			   pv_table(),
	    	   pv_arr(kMaxSearchDepth),
	    	   search_hist(kNumPceTypes, std::vector<int32_t>(kBoardArraySize)),
	    	   search_killers(kNumPlayers, std::vector<Move>(kMaxSearchDepth))

{
	for(uint32_t pce = 0; pce < kNumPceTypes; ++pce)
	{
		this->piece_list[pce].reserve(10);
	}
	this->parseFEN(STARTFEN);
}

Board::Board(const std::string fen) noexcept :
									pieces(kBoardArraySize),
									pawns(3), 
									king_sq(kNumPlayers), 
								    side_to_move(WHITE),
								    en_pas(NO_SQ),
								    fifty_move(0),
								    ply(0),
								    hist_ply(0),
								    pos_key(0),
								    castle_perm(0xf),
			   						piece_list(kNumPceTypes, std::vector<uint32_t>()),
									big_pce(kNumPlayers),
									maj_pce(kNumPlayers), 
									min_pce(kNumPlayers), 
									material(kNumPlayers), 
									history(kMoveLimit),
									pv_table(),
									pv_arr(kMaxSearchDepth),
									search_hist(kNumPceTypes, std::vector<int32_t>(kBoardArraySize)),
									search_killers(kNumPlayers, std::vector<Move>(kMaxSearchDepth))
{
	for(uint32_t pce = 0; pce < kNumPceTypes; ++pce)
	{
		this->piece_list[pce].reserve(10);
	}
	this->parseFEN(fen);
}

void Board::resetBoard(void) noexcept
{
	for(uint32_t i = 0; i < kBoardArraySize; ++i)
	{
		this->pieces[i] = OFFBOARD;
	}

	for(uint32_t i = 0; i < kChessboardSize; ++i)
	{
		this->pieces[BoardUtils::Sq64ToSq120[i]] = EMPTY;
	}

	for(uint32_t i = 0; i < kNumPlayers; ++i)
	{
		this->big_pce[i] = 0;
		this->maj_pce[i] = 0;
		this->min_pce[i] = 0;
		this->material[i] = 0;
		this->pawns[i] = 0;
	}
	this->pawns[2] = 0;

	for(uint32_t i = 0; i < kNumPceTypes; ++i)
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
void Board::setUpPieces(const std::string& section) noexcept
{
	int fenIdx = 0;
	for(int32_t rank = RANK_8; rank >= RANK_1; rank --)
	{
		for(uint32_t file = FILE_A; file <= FILE_H; ++file)
		{
			if(isdigit(section[fenIdx]))
			{
				for(int32_t i = 0; i < section[fenIdx] - '0'; ++i)
				{
					this->pieces[fileRankToSq(file, rank)] = EMPTY;
					++file;
				}
				file--;

			}
			else
			{
				switch(section[fenIdx])
				{
					case 'p':this->pieces[fileRankToSq(file, rank)] = bP;break;
					case 'n':this->pieces[fileRankToSq(file, rank)] = bN;break;
					case 'b':this->pieces[fileRankToSq(file, rank)] = bB;break;
					case 'r':this->pieces[fileRankToSq(file, rank)] = bR;break;
					case 'q':this->pieces[fileRankToSq(file, rank)] = bQ;break;
					case 'k':this->pieces[fileRankToSq(file, rank)] = bK;break;
					case 'P':this->pieces[fileRankToSq(file, rank)] = wP;break;
					case 'N':this->pieces[fileRankToSq(file, rank)] = wN;break;
					case 'B':this->pieces[fileRankToSq(file, rank)] = wB;break;
					case 'R':this->pieces[fileRankToSq(file, rank)] = wR;break;
					case 'Q':this->pieces[fileRankToSq(file, rank)] = wQ;break;
					case 'K':this->pieces[fileRankToSq(file, rank)] = wK;break;
				}
			}
			++fenIdx;
		}
		++fenIdx;
	}
}

void Board::setUpCastlePerm(const std::string& section) noexcept
{
	this->castle_perm = 0;
	if(section[0] != '-')
	{
		for(uint32_t i = 0; i < section.size(); ++i )
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
}


void Board::getenPassant(const std::string& section) noexcept
{
	if(section != "-")
	{
		int file = section[0] - 'a';
		int rank = section[1] - '1';
		this->en_pas = fileRankToSq(file, rank);
	}
}

void Board::setUpMoveCounters(std::istringstream& stream, std::string& section) noexcept
{
	using namespace std;

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
}

void Board::parseFEN(const std::string fen) noexcept
{
	using namespace std;

	this->resetBoard();

	std::istringstream stream(fen);
	std::string section;

	// piece locations 
	std::getline(stream, section, ' ');
	this->setUpPieces(section);

	// side to move
	std::getline(stream, section, ' ');
	this->side_to_move = section[0] == 'w' ? WHITE : BLACK;

	// Castling permissions
	std::getline(stream, section, ' ');
	this->setUpCastlePerm(section);

	// En Passant Square
	std::getline(stream, section, ' ');
	this->getenPassant(section);

	// halfmove clock (halfmoves since capture or pawn advance)
	std::getline(stream, section, ' ');
	this->setUpMoveCounters(stream, section);

	this->pos_key = Hash::generatePosKey(*this);
	this->updatePieceLists();
}

void Board::updatePieceLists() noexcept
{
	for(uint32_t index = 0; index < kBoardArraySize; ++index)
	{
		int piece = this->pieces[index];
		// on board
		if( isPiece(piece) )
		{
			int color = PieceInfo::PieceCol[piece];
			this->big_pce[color] += PieceInfo::PieceBig[piece];
			this->maj_pce[color] += PieceInfo::PieceMaj[piece];
			this->min_pce[color] += PieceInfo::PieceMin[piece];
			this->material[color] += PieceInfo::PieceVal[piece];

			this->piece_list[piece].push_back(index);

			if(piece == wK) this->king_sq[WHITE] = index;
			if(piece == bK) this->king_sq[BLACK] = index;

			if(piece == wP) 
			{
				BB::setBit(this->pawns[WHITE], BoardUtils::Sq120ToSq64[index]);
				BB::setBit(this->pawns[BOTH], BoardUtils::Sq120ToSq64[index]);
			}
			if(piece == bP) 
			{
				BB::setBit(this->pawns[BLACK], BoardUtils::Sq120ToSq64[index]);
				BB::setBit(this->pawns[BOTH], BoardUtils::Sq120ToSq64[index]);
			}
		}
	}
}

bool checkBoard(const Board& pos) noexcept
{
	uint32_t t_pceNum[kNumPceTypes] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint32_t t_bigPce[kNumPlayers] = { 0, 0};
	uint32_t t_majPce[kNumPlayers] = { 0, 0};
	uint32_t t_minPce[kNumPlayers] = { 0, 0};
	uint32_t t_material[kNumPlayers] = { 0, 0};
	uint32_t sq64,t_piece,t_pce_num,sq120,colour,pcount;
	uint64_t t_pawns[3] = {0ULL, 0ULL, 0ULL};
	
	t_pawns[WHITE] = pos.pawns[WHITE];
	t_pawns[BLACK] = pos.pawns[BLACK];
	t_pawns[BOTH] = pos.pawns[BOTH];
	
	// check piece lists
	for(t_piece = wP; t_piece <= bK; ++t_piece) 
	{
		for(t_pce_num = 0; t_pce_num < pos.piece_list[t_piece].size(); ++t_pce_num) 
		{
			sq120 = pos.piece_list[t_piece][t_pce_num];
			ASSERT(pos.pieces[sq120]==t_piece);
		}	
	}
	// check piece count and other counters	
	for(sq64 = 0; sq64 < kChessboardSize; ++sq64) 
	{
		sq120 = BoardUtils::Sq64ToSq120[sq64];
		t_piece = pos.pieces[sq120];
		++t_pceNum[t_piece];
		colour = PieceInfo::PieceCol[t_piece];
		if( PieceInfo::PieceBig[t_piece] == true) ++t_bigPce[colour];
		if( PieceInfo::PieceMin[t_piece] == true) ++t_minPce[colour];
		if( PieceInfo::PieceMaj[t_piece] == true) ++t_majPce[colour];	
		t_material[colour] += PieceInfo::PieceVal[t_piece];
	}
	for(t_piece = wP; t_piece <= bK; ++t_piece) 
	{
		ASSERT(t_pceNum[t_piece]==pos.piece_list[t_piece].size());	
	}
	// check bitboards count
	pcount = BB::countBits(t_pawns[WHITE]);
	ASSERT(pcount == pos.piece_list[wP].size());
	pcount = BB::countBits(t_pawns[BLACK]);
	ASSERT(pcount == pos.piece_list[bP].size());
	pcount = BB::countBits(t_pawns[BOTH]);
	ASSERT(pcount == (pos.piece_list[bP].size() + pos.piece_list[wP].size()));
	(void) pcount;
	// check bitboards squares
	while(t_pawns[WHITE]) 
	{
		sq64 = BB::popBit(t_pawns[WHITE]);
		ASSERT(pos.pieces[BoardUtils::Sq64ToSq120[sq64]] == wP);
	}
	while(t_pawns[BLACK]) 
	{
		sq64 = BB::popBit(t_pawns[BLACK]);
		ASSERT(pos.pieces[BoardUtils::Sq64ToSq120[sq64]] == bP);
	}
	while(t_pawns[BOTH]) 
	{
		sq64 = BB::popBit(t_pawns[BOTH]);
		ASSERT( (pos.pieces[BoardUtils::Sq64ToSq120[sq64]] == bP) || (pos.pieces[BoardUtils::Sq64ToSq120[sq64]] == wP) );
	}	
	ASSERT(t_material[WHITE]==pos.material[WHITE] && t_material[BLACK]==pos.material[BLACK]);
	ASSERT(t_minPce[WHITE]==pos.min_pce[WHITE] && t_minPce[BLACK]==pos.min_pce[BLACK]);
	ASSERT(t_majPce[WHITE]==pos.maj_pce[WHITE] && t_majPce[BLACK]==pos.maj_pce[BLACK]);
	ASSERT(t_bigPce[WHITE]==pos.big_pce[WHITE] && t_bigPce[BLACK]==pos.big_pce[BLACK]);	
	ASSERT(pos.side_to_move==WHITE || pos.side_to_move==BLACK);	
	ASSERT(pos.en_pas==NO_SQ || ( BoardUtils::RankBrd[pos.en_pas]==RANK_6 && pos.side_to_move == WHITE)
		 || ( BoardUtils::RankBrd[pos.en_pas]==RANK_3 && pos.side_to_move == BLACK));
	ASSERT(pos.pieces[pos.king_sq[WHITE]] == wK);
	ASSERT(pos.pieces[pos.king_sq[BLACK]] == bK);
		 
	return true;
}


bool Board::sqOnBoard(uint32_t sq) const noexcept
{
	return !(this->pieces[sq] == OFFBOARD || this->pieces[sq] == NO_SQ);
}

uint32_t Board::sqAttacked(const uint32_t sq, const uint32_t attacker) const noexcept
{
	uint32_t numAttackers = 0;
	// Check Pawn
	if(attacker == WHITE)
	{
		if(this->pieces[sq + Attack::wPCap[0]] == wP)
			++numAttackers;
		if(this->pieces[sq + Attack::wPCap[1]] == wP)
			++numAttackers;
	}
	else
	{
		if(this->pieces[sq + Attack::bPCap[0]] == bP)
			++numAttackers;
		if(this->pieces[sq + Attack::bPCap[1]] == bP)
			++numAttackers;
	}
	// Check Knight
	uint32_t attackingKnight = attacker == WHITE ? wN : bN;
	for(uint32_t i = 0; i < Attack::KnMoves.size(); ++i)
	{
		if(this->pieces[sq + Attack::KnMoves[i]] == attackingKnight)
			++numAttackers;
	}
	// Check Horizontal and Vertical
	uint32_t attackingRook = attacker == WHITE ? wR : bR;
	uint32_t attackingQueen = attacker == WHITE ? wQ : bQ;
	for(uint32_t i = 0 ; i < Attack::RkMoves.size(); ++i )
	{
		uint32_t move = Attack::RkMoves[i];
		uint32_t t_sq = sq + move;
		uint32_t pce = this->pieces[t_sq];
		while(pce != OFFBOARD)
		{
			if(pce != EMPTY)
			{
				if(pce == attackingRook || pce == attackingQueen)
					++numAttackers;
				break;
			}
			t_sq += move;
			pce = this->pieces[t_sq];
		}
	}
	uint32_t attackingBishop = attacker == WHITE ? wB : bB;
	for(uint32_t i = 0 ; i < Attack::BiMoves.size(); ++i )
	{
		uint32_t move = Attack::BiMoves[i];
		uint32_t t_sq = sq + move;
		uint32_t pce = this->pieces[t_sq];
		while(pce != OFFBOARD)
		{
			if(pce != EMPTY)
			{
				if(pce == attackingBishop || pce == attackingQueen)
					++numAttackers;
				break;
			}
			t_sq += move;
			pce = this->pieces[t_sq];
		}
	}
	uint32_t attackingKing = attacker == WHITE ? wK : bK;
	for(uint32_t i = 0; i < Attack::KiMoves.size(); ++i)
	{
		if(this->pieces[sq + Attack::KiMoves[i]] == attackingKing)
			++numAttackers;
	}
	return numAttackers;
}

MoveList Board::getAllMoves() const noexcept
{
	MoveList m;
	m.generateAllMoves(*this);
	return m;
}

MoveList Board::getAllCaptureMoves() const noexcept
{
	MoveList m;
	m.generateAllCaptureMoves(*this);
	return m;
}

void Board::flipBoard() noexcept
{
	using namespace BoardUtils;
	std::array<int32_t, kChessboardSize> tmpPieceArray;
	std::array<int32_t, kNumPceTypes> inversePieceEnum {EMPTY, bP, bN, bB, bR, bQ, bK, wP, wN, wB, wR, wQ, wK};
	int32_t tmpSide = !this->side_to_move;
	int32_t tmpCastlePerm = 0;
	int32_t tmpEnPas = NO_SQ;

	if(this->castle_perm & WKCA) tmpCastlePerm |= BKCA;
	if(this->castle_perm & WQCA) tmpCastlePerm |= BKCA;
	if(this->castle_perm & BKCA) tmpCastlePerm |= WKCA;
	if(this->castle_perm & BQCA) tmpCastlePerm |= WQCA;
	if(this->en_pas != NO_SQ) tmpEnPas = Sq64ToSq120[WhiteToBlack[this->en_pas]];

	for(uint32_t sq = 0; sq < kChessboardSize; ++sq)
	{
		tmpPieceArray[sq] = this->pieces[Sq64ToSq120[WhiteToBlack[sq]]];
	}
	this->resetBoard();
	for(uint32_t sq = 0; sq < kChessboardSize; ++sq)
	{
		int32_t tmpPiece = inversePieceEnum[tmpPieceArray[sq]];
		this->pieces[Sq64ToSq120[sq]] = tmpPiece;
	}
	this->side_to_move = tmpSide;
	this->castle_perm = tmpCastlePerm;
	this->en_pas = tmpEnPas;
	this->pos_key = Hash::generatePosKey(*this);
	this->updatePieceLists();
	ASSERT(checkBoard(*this));
}


bool Board::inCheck() noexcept
{
	return this->sqAttacked(this->king_sq[this->side_to_move], !this->side_to_move);
}

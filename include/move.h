#ifndef MOVE_H
#define MOVE_H

#include <string>
class Board;
// used for undoing
class UndoMove
{
	public:
		int32_t move;
		int32_t castle_perm;
		int32_t en_pas;
		int32_t fifty_move;
		uint64_t pos_key;
		UndoMove();
		UndoMove(int32_t _move, const Board& pos);
};

namespace MoveFlags
{
	constexpr int32_t SQ = 0x7F;
	constexpr int32_t EP = 0x40000;
	constexpr int32_t PS = 0x80000;
	constexpr int32_t CA = 0x1000000;
	constexpr int32_t CAP = 0x7C000;
	constexpr int32_t PROM = 0xF00000;
}
class Move
{
	public:
		uint32_t move;
		int32_t score;
		Move(uint32_t from, uint32_t to, uint32_t captured, uint32_t prom, uint32_t flag) noexcept;
		Move(uint32_t _move, int32_t _score) noexcept;
		Move(uint32_t _move) noexcept;
		Move(const Move& o) noexcept;
		Move(Move&& o) noexcept;
		Move() noexcept;

		// 7 bits for src
		constexpr uint32_t from() const { return this->move & MoveFlags::SQ; }
		// 7 bits for dest 
		constexpr uint32_t to() const { return (this->move >> 7) & MoveFlags::SQ; }
		// 4 bits for which piece was captured if any
		constexpr uint32_t captured() const { return (this->move >> 14) & 0xf; }
		// 1 bit for enPas
		constexpr uint32_t enPassant() const {  return this->move & MoveFlags::EP; }
		// 1 bit for pawn start 
		constexpr uint32_t pawnStart() const { return this->move & MoveFlags::PS; }
		// 4 bits for which piece was captured if any
		constexpr uint32_t promoted() const { return (this->move & MoveFlags::PROM) >> 20; }
		// 1 bit for Castle move
		constexpr uint32_t castle() const { return this->move & MoveFlags::CA; }
		
		constexpr bool isNull() const { return this->move == 0; }
		constexpr bool wasCapture() const { return this->move & MoveFlags::CAP; }
		constexpr bool wasPromotion() const { return this->move & MoveFlags::PROM; }

		const std::string toString() const noexcept;

		Move& operator=(const Move& o) noexcept;
		Move& operator=(Move&& o) noexcept;
		bool operator==(const Move& rhs) const noexcept;
		bool operator!=(const Move& rhs) const noexcept;
};

#endif

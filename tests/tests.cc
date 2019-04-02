#define CATCH_CONFIG_MAIN
#include<../lib/catch2/catch.hpp>
#include<../include/board.h>
#include<../include/movemaker.h>
#include<../include/tester.h>
#include<../include/stopwatch.h>
#define STARTFEN  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define TESTFEN "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"

TEST_CASE("We can instantiate a board and make moves")
{
	enum { WHITE, BLACK, BOTH };
	enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
	SECTION("Board should be the starting board by default")
	{
		Board b;
		REQUIRE(b.pawns[WHITE] == 0x000000000000FF00);
		REQUIRE(b.pawns[BLACK] == 0x00FF000000000000);
		REQUIRE(b.pawns[BOTH]  == 0x00FF00000000FF00);
		
		REQUIRE(b.piece_list[wP].size() == 8);
		REQUIRE(b.piece_list[wN].size() == 2);
		REQUIRE(b.piece_list[wB].size() == 2);
		REQUIRE(b.piece_list[wR].size() == 2);
		REQUIRE(b.piece_list[wQ].size() == 1);
		REQUIRE(b.piece_list[wK].size() == 1);


		REQUIRE(b.piece_list[bP].size() == 8);
		REQUIRE(b.piece_list[bN].size() == 2);
		REQUIRE(b.piece_list[bB].size() == 2);
		REQUIRE(b.piece_list[bR].size() == 2);
		REQUIRE(b.piece_list[bQ].size() == 1);
		REQUIRE(b.piece_list[bK].size() == 1);

		REQUIRE(b.inCheck() == false);
	}

	SECTION("We can parse a FEN and set up the board")
	{
		Board b(STARTFEN);
		REQUIRE(b.pawns[WHITE] == 0x000000000000FF00);
		REQUIRE(b.pawns[BLACK] == 0x00FF000000000000);
		REQUIRE(b.pawns[BOTH]  == 0x00FF00000000FF00);
		
		REQUIRE(b.piece_list[wP].size() == 8);
		REQUIRE(b.piece_list[wN].size() == 2);
		REQUIRE(b.piece_list[wB].size() == 2);
		REQUIRE(b.piece_list[wR].size() == 2);
		REQUIRE(b.piece_list[wQ].size() == 1);
		REQUIRE(b.piece_list[wK].size() == 1);


		REQUIRE(b.piece_list[bP].size() == 8);
		REQUIRE(b.piece_list[bN].size() == 2);
		REQUIRE(b.piece_list[bB].size() == 2);
		REQUIRE(b.piece_list[bR].size() == 2);
		REQUIRE(b.piece_list[bQ].size() == 1);
		REQUIRE(b.piece_list[bK].size() == 1);

		REQUIRE(b.inCheck() == false);
	}

	SECTION("We can parse a complex FEN and set up the board")
	{
		Board b(STARTFEN);
		REQUIRE(b.pawns[WHITE] == 0x0000000000000000);
		REQUIRE(b.pawns[BLACK] == 0x0000000000000000);
		REQUIRE(b.pawns[BOTH]  == 0x0000000000000000);
		
		REQUIRE(b.piece_list[wP].size() == 0);
		REQUIRE(b.piece_list[wN].size() == 0);
		REQUIRE(b.piece_list[wB].size() == 0);
		REQUIRE(b.piece_list[wR].size() == 2);
		REQUIRE(b.piece_list[wQ].size() == 0);
		REQUIRE(b.piece_list[wK].size() == 1);


		REQUIRE(b.piece_list[bP].size() == 0);
		REQUIRE(b.piece_list[bN].size() == 0);
		REQUIRE(b.piece_list[bB].size() == 0);
		REQUIRE(b.piece_list[bR].size() == 2);
		REQUIRE(b.piece_list[bQ].size() == 0);
		REQUIRE(b.piece_list[bK].size() == 1);

		REQUIRE(b.inCheck() == false);
	}
}

TEST_CASE("We can correctly generate moves")
{
	SECTION("Check start board move gen")
	{
		Board b(STARTFEN);
		MoveList ml = b.getAllMoves();
		REQUIRE(ml.size() == 20);

		MoveList ml2 = b.getAllCaptureMoves();
		REQUIRE(ml2.size() == 0);
	}

	SECTION("Check test FEN move gen")
	{
		Board b(TESTFEN);
		MoveList ml = b.getAllMoves();
		REQUIRE(ml.size() == 26);

		MoveList ml2 = b.getAllCaptureMoves();
		REQUIRE(ml2.size() == 2);
	}
}

TEST_CASE("We can run the perft tester")
{
	SECTION("Running Perft Tester, please verify output")
	{
		Engine::getInstance();
		Board b;
		PerftTester p;
		Stopwatch s;
		s.start();
		p.perftTest(6, b, true);
		std::cout << s.stop() <<std::endl;
	}
}

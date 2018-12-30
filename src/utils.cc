#include "utils.h"
#include "defs.h"
#include "io.h"
#include "movelist.h"
#include "movemaker.h"
#include <unistd.h>
#include <random>
#include <sstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>

#ifdef WIN32
#include "windows.h"
#else
#include "sys/time.h"
#include "sys/select.h"
#include "string.h"
#endif


bool sqOnBoard(uint32_t sq) noexcept
{
	return BoardUtils::Sq120ToSq64[sq] != 65;
}

//return the 120 sq value of a given file and rank
int fileRankToSq(int file, int rank) noexcept
{
	return 21 + file + rank * 10;
}

bool isPiece(int piece) noexcept
{
	return (piece != OFFBOARD && piece != EMPTY && piece != NO_SQ);
}

std::string sqToString(const int sq) noexcept
{
	std::ostringstream stream;
	char file = 'a' + BoardUtils::FileBrd[sq];
	char rank = '1' + BoardUtils::RankBrd[sq];
	stream<<file<<rank;
	return stream.str();
}
 
//https://stackoverflow.com/questions/37396278/how-to-generate-very-large-random-number-in-c
uint64_t randU64() noexcept
{
	using namespace std;
	/* Seed */
	random_device rd;

	/* Random number generator */
	default_random_engine generator(rd());

	/* Distribution on which to apply the generator */
	uniform_int_distribution<uint64_t> distribution(0,0xFFFFFFFFFFFFFFFF);
	return distribution(generator);
}


void showAttackedSqs(const int side,Board& pos) noexcept
{
	int rank = 0;
	int file = 0;
	int sq = 0;
	
	printf("\n\nSquares attacked by:%c\n",IO::SideChar[side]);
	for(rank = RANK_8; rank >= RANK_1; --rank) {
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = fileRankToSq(file,rank);
			int numAtk = pos.sqAttacked(sq, side);
			printf("%i",numAtk );
				
		}
		printf("\n");
	}  
    printf("\n\n");

}

void stringToLower(std::string& str) noexcept
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// http://home.arcor.de/dreamlike/chess/
// All credits go to above for the following code
int InputWaiting()
{
#ifndef WIN32
  fd_set readfds;
  struct timeval tv;
  FD_ZERO (&readfds);
  FD_SET (fileno(stdin), &readfds);
  tv.tv_sec=0; tv.tv_usec=0;
  select(16, &readfds, 0, 0, &tv);

  return (FD_ISSET(fileno(stdin), &readfds));
#else
   static int init = 0, pipe;
   static HANDLE inh;
   DWORD dw;

   if (!init) {
     init = 1;
     inh = GetStdHandle(STD_INPUT_HANDLE);
     pipe = !GetConsoleMode(inh, &dw);
     if (!pipe) {
        SetConsoleMode(inh, dw & ~(ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT));
        FlushConsoleInputBuffer(inh);
      }
    }
    if (pipe) {
      if (!PeekNamedPipe(inh, NULL ,0, NULL, &dw, NULL)) return 1;
      return dw;
    } else {
      GetNumberOfConsoleInputEvents(inh, &dw);
      return dw <= 1 ? 0 : dw;
	}
#endif
}

// Can probably change this to use C++ I/O
void ReadInput(SearchInfo& info) {
  int             bytes;
  char            input[256] = "", *endc;

    if (InputWaiting()) {    
		info.stopped = true;
		do {
		  bytes=read(fileno(stdin),input,256);
		} while (bytes<0);
		endc = strchr(input,'\n');
		if (endc) *endc=0;

		if (strlen(input) > 0) {
			if (!strncmp(input, "quit", 4))    {
			  info.quit = true;
			}
		}
		return;
    }
}

// //c++ version, not 100% sure if working
// void ReadInput(SearchInfo& info)
// {
// 	std::string buf;
//     if (InputWaiting()) {    
// 		info.stopped = true;
// 		getline(std::cin, buf);
// 		std::replace(buf.begin(), buf.end(), '\n', '\0');
// 		if(buf.substr(0, 4) == "quit")
// 		{
// 			info.quit = true;
// 		}
//     }
// }
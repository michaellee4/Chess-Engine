#ifndef UCI_H
#define UCI_H
#include"board.h"
#include "searchinfo.h"
#include<string>
	
//might need newline at the end of this string
const std::string UCI_STARTPOS = "position startpos";

void parseGoCmd(const std::string& cmd, SearchInfo& info, Board& pos);
void parsePosition(const std::string& input, Board& pos);
void UCILoop();
#endif
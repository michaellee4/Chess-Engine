#ifndef UCI_H
#define UCI_H
#include"board.h"
#include "searchinfo.h"
#include "search.h"
#include<string>
	
//might need newline at the end of this string
class UCIManager
{
	const std::string UCI_STARTPOS = "position startpos";
	Board pos;
	SearchInfo info;
	SearchAgent sa;
public:
	void parseGoCmd(const std::string& cmd);
	void parsePosition(const std::string& input);
	void UCILoop();
	UCIManager() noexcept;
};

#endif
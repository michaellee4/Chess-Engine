#ifndef CONSOLE_H
#define CONSOLE_H

#include"board.h"
#include "searchinfo.h"
#include "search.h"
#include "protocol.h"

class ConsoleManager : public ProtocolManager
{
public:
	void loop() override;
	ConsoleManager() noexcept;
	~ConsoleManager() noexcept;
};


#endif
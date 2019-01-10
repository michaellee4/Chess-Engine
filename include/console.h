#ifndef CONSOLE_H
#define CONSOLE_H
#include "protocol.h"

/**
 * See ProtocolManager documentation
 */
class ConsoleManager : public ProtocolManager
{
public:
	void loop() override;
	int32_t getProtocol() override;
	ConsoleManager() noexcept;
	~ConsoleManager() noexcept;
};


#endif
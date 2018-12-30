#ifndef UCI_H
#define UCI_H
#include "protocol.h"
#include<string>
	
//might need newline at the end of this string
class UCIManager : public ProtocolManager
{
public:
	void parseGoCmd(const std::string& cmd);
	void parsePosition(const std::string input);
	void loop() override;
	int32_t getProtocol() override;
	UCIManager() noexcept;
	~UCIManager() noexcept;
};

#endif
#ifndef ENGINE_H
#define ENGINE_H
#include <memory>
#include "protocol.h"

class Engine
{
public:
	static Engine& getInstance()
	{
		static Engine instance;
		return instance;
	}
private:
	Engine() noexcept;
	void printGreeting() const noexcept;
	std::unique_ptr<ProtocolManager> protocol;
public:
	Engine(const Engine&) = delete;
	void operator=(const Engine&) = delete;
	void start() noexcept;
};

#endif
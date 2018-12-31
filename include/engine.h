#ifndef ENGINE_H
#define ENGINE_H
#include <memory>
#include "protocol.h"
#include "polyglot.h"

struct EngineConfig
{
	bool useBook;
	EngineConfig() : useBook(true) {}
};

class Engine
{
public:
	static Engine& getInstance()
	{
		static Engine instance;
		return instance;
	}
	static EngineConfig& getConfig()
	{
		return Engine::getInstance().config;
	}
	static PolyBook& getBook()
	{
		return Engine::getInstance().book;
	}
private:
	Engine() noexcept;
	void printGreeting() const noexcept;
	std::unique_ptr<ProtocolManager> protocol;
	EngineConfig config;
	PolyBook book;
public:
	Engine(const Engine&) = delete;
	void operator=(const Engine&) = delete;
	void start() noexcept;
};

#endif
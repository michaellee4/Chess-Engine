/**
*	@file engine.h
*	@brief Defines the central engine data structure
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef ENGINE_H
#define ENGINE_H
#include <memory>
#include "protocol.h"
#include "polyglot.h"

/**
	@brief Stores the flags for the engine.
 */
struct EngineConfig
{
	bool useBook;
	EngineConfig() : useBook(true) {}
};

class Engine
{
public:
/**
	@brief Gets the instance of the Engine singleton.
	@param None
	@return The Engine instance
 */
	static Engine& getInstance()
	{
		static Engine instance;
		return instance;
	}
/**
	@brief Gets the instance of the Engine config.
	@param None
	@return The Engine config
 */
	static EngineConfig& getConfig()
	{
		return Engine::getInstance().config;
	}
/**
	@brief Gets the Polyglot opening book that is being used by the engine.
	@param None
	@return The Polyglot opening book that the engine is using.
 */
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
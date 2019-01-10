/**
*	@file stopwatch.h
*	@brief Contains declarations of functions for basic benchmarking and timing.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <unistd.h>

class Stopwatch
{
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
	private:
		Time::time_point start_time;
	public:
		static constexpr int32_t kMilliPerSecond = 1000;
		static constexpr int32_t kSecondsPerMinute = 60;
		Stopwatch() noexcept;
		~Stopwatch() noexcept;
/**
	@brief Starts the internal timer.
	@param None
	@return None
 */
		void start() noexcept;
/**
	@brief Stops the internal timer and returns the time elapsed.
	@param None
	@return The time elapsed since start() was called in milliseconds.
 */
		float stop() noexcept;

/**
	@brief Get the time since the epoch in milliseconds.
	@param None
	@return Get the time since the epoch in milliseconds
 */
		static uint64_t getTimeInMilli() noexcept;
};

#endif

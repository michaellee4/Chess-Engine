#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <unistd.h>

/**
 * This class provides some basic benchmarking and timing functions
 */
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
		 * Input: None
		 * Output: None
		 * Operation: Starts the internal timer.
		 */
		void start() noexcept;

		/**
		 * Input: None
		 * Output: The time elapsed since start() was called in milliseconds
		 * Operation: None
		 */
		float stop() noexcept;

		/**
		 * Input: None
		 * Output: Time since the epoch in milliseconds.
		 * Operation: None
		 */
		static uint64_t getTimeInMilli() noexcept;
};

#endif

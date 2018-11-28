#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <unistd.h>
#include <cstdio>

// Simple stopwatch class for benchmarking
class Stopwatch
{
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
	private:
		Time::time_point start_time;
	public:
		Stopwatch();
		~Stopwatch();
		void start();
		float stop();

};

#endif
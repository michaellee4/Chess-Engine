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
		static uint64_t getTimeInMilli();
};

Stopwatch::Stopwatch()
{
	this->start();
}
Stopwatch::~Stopwatch()
{
	this->stop();
}
void Stopwatch::start()
{
	start_time = Time::now();
}
float Stopwatch::stop()
{
	auto dur = std::chrono::duration_cast<ms>(Time::now() - start_time);
	float milli = dur.count();
	return milli;
}

uint64_t Stopwatch::getTimeInMilli()
{
	using namespace std::chrono;
	milliseconds ms = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch());
	return ms.count();
}
#endif

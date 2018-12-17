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
	printf("Elapsed Time: %.3f seconds\n", milli / 1000 );
	return dur.count();
}


#endif
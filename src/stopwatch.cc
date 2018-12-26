#include "stopwatch.h"

Stopwatch::Stopwatch() : start_time(Time::now()) {}
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
	milliseconds milli= duration_cast< milliseconds >(
    system_clock::now().time_since_epoch());
	return milli.count();
}

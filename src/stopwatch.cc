#include "stopwatch.h"

Stopwatch::Stopwatch() noexcept : start_time(Time::now()) {}
Stopwatch::~Stopwatch() noexcept
{
	this->stop();
}
void Stopwatch::start() noexcept
{
	start_time = Time::now();
}
float Stopwatch::stop() noexcept
{
	auto dur = std::chrono::duration_cast<ms>(Time::now() - start_time);
	float milli = dur.count();
	return milli;
}

uint64_t Stopwatch::getTimeInMilli() noexcept
{
	using namespace std::chrono;
	milliseconds milli= duration_cast< milliseconds >(
    system_clock::now().time_since_epoch());
	return milli.count();
}

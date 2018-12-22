#include "stopwatch.h"

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
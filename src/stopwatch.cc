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
	printf("Elapsed Time: %.3f seconds\n", milli / 1000 );
	return dur.count();
}

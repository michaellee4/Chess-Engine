/**
*	@file searchinfo.h
*	@brief Contains information about the search constraints provided by the engine
*	@author Michael Lee
*	@date 1/9/2019
*/

#ifndef SEARCHINFO_H
#define SEARCHINFO_H

struct SearchInfo
{
	uint64_t startTime;
	uint64_t stopTime;
	bool timeLimit;

	uint32_t depth;
	uint32_t depthLimit;

	uint32_t nodes;

	uint32_t movesLeft;

	// flags
	bool infinite;
	bool quit;
	bool stopped;

	float fh;
	float fhf;

	int32_t protocol;
	bool doPrint;
	
	constexpr SearchInfo() noexcept: startTime(0),
				   stopTime(0),
				   timeLimit(false),
				   depth(0),
				   depthLimit(0),
				   nodes(0),
				   movesLeft(0),
				   infinite(false),
				   quit(false),
				   stopped(false),
				   fh(0),
				   fhf(0),
				   protocol(2),
				   doPrint(false){}
};


#endif

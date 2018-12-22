#ifndef SEARCHINFO_H
#define SEARCHINFO_H

struct SearchInfo
{
	uint64_t startTime;
	uint64_t stopTime;
	uint64_t timeLimit;

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
};


#endif

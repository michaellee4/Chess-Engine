#ifndef SEARCHINFO_H
#define SEARCHINFO_H

class SearchInfo
{
public:
	uint32_t startTime;
	uint32_t stopTime;
	uint32_t timeLimit;

	uint32_t depth;
	uint32_t depthLimit;

	uint32_t nodes;

	uint32_t movesLeft;

	// flags
	bool infinite;
	bool quit;
	bool stopped;
};


#endif

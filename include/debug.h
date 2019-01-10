/**
*	@file debug.h
*	@brief Defines an assert function for debugging.
*	@author Michael Lee
*	@date 1/9/2019
*/
#ifndef DEBUG_H
#define DEBUG_H

#include <stdlib.h>

// #define DEBUG

// Tests if n is true. End the program and indicate line # if the assertion fails.
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif


#endif
#ifndef DEBUG_H
#define DEBUG_H

#include <stdlib.h>

#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed In File %s Line %d\n", #n, __FILE__, __LINE__); \
exit(1);}

#endif
#ifndef _IPL_MEMORY_H_INCLUDE_
#define _IPL_MEMORY_H_INCLUDE_

#include "iplDefine.h"
#include "iplTypes.h"


extern void* (*iplmemcpy )(void *dts, const void *src, size_t nbytes);
extern void* (*iplmemzero)(void *dts, size_t nbytes);



#endif//_IPL_MEMORY_H_INCLUDE_

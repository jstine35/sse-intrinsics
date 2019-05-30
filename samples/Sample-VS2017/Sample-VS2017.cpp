
// Main purpose of this sample is to verify compilation of both 32 and 64 bit versions
// the library under "bare header" conditions.

#include <cstdio>
#include <cstdint>

#include "sse_intrinsics.h"

int main()
{
	__m128 zeros;
	__m128 negones;
	__m128 ones;

	i_setzero(zeros);
	i_setFFs (negones);
	i_psubd  (ones, zeros, negones);

	uint32_t* parts = (uint32_t*)&ones;
	printf("%08x %08x %08x %08x\n", parts[0], parts[1], parts[2], parts[3]);
}

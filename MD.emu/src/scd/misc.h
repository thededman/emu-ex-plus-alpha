#pragma once

#include <imagine/util/ansiTypes.h>

typedef struct
{
	int b0;
	int b1;
	int b2;
	int b3;
	int b4;
	int b5;
	int b6;
	int b7;
} intblock;

static void memcpy32(int *dest, int *src, uint count)
{
	intblock *bd = (intblock *) dest, *bs = (intblock *) src;

	for (; count >= sizeof(*bd)/4; count -= sizeof(*bd)/4)
		*bd++ = *bs++;

	dest = (int *)bd; src = (int *)bs;
	while (count--)
		*dest++ = *src++;
}

static void memcpy16(unsigned short *dest, unsigned short *src, uint count)
{
	if ((((ptrsize)dest | (ptrsize)src) & 3) == 0)
	{
		if (count >= 32) {
			memcpy32((int *)dest, (int *)src, count/2);
			count&=1;
		} else {
			for (; count >= 2; count -= 2, dest+=2, src+=2)
				*(int *)dest = *(int *)src;
		}
	}
	while (count--)
		*dest++ = *src++;
}


static void memcpy16bswap(unsigned short *dest, void *src, uint count)
{
	uchar *src_ = (uchar*)src;

	for (; count; count--, src_ += 2)
		*dest++ = (src_[0] << 8) | src_[1];
}

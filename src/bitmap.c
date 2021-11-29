#include "bitmap.h"


#include <proto/graphics.h>

/*--------------------------------------------------------------------------*/

struct BitMap* BitmapDisplayable(struct Dimension* dim)
{
	const ULONG flags = BMF_CLEAR | BMF_DISPLAYABLE | BMF_INTERLEAVED;

	return AllocBitMap(dim->width, dim->height, dim->depth, flags, NULL);
}

/*--------------------------------------------------------------------------*/

void BitmapFree(struct BitMap* bm)
{
	FreeBitMap(bm);
}

/*--------------------------------------------------------------------------*/
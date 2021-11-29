#ifndef DTWB_BITMAP_H
#define DTWB_BITMAP_H
/*--------------------------------------------------------------------------*/

#include "types.h"

struct BitMap* BitmapDisplayable(struct Dimension* dim);

void BitmapFree(struct BitMap* bm);

/*--------------------------------------------------------------------------*/
#endif /* DTWB_BITMAP_H */

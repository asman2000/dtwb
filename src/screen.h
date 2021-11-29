#ifndef DTWB_SCREEN_H
#define DTWB_SCREEN_H
/*--------------------------------------------------------------------------*/
#include "types.h"

int ScreenOpen(void);
void ScreenClose(void);

ULONG ScreenGetAddress(void);

struct RastPort* ScreenGetRastPort(void);

/*--------------------------------------------------------------------------*/
#endif /* DTWB_SCREEN_H */

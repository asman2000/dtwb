#include "gfx.h"


#include "screen.h"
#include "utils.h"
#include "window.h"
#include "types.h"

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/datatypes.h>
#include <datatypes/pictureclass.h> 

#include <stdio.h>
/*--------------------------------------------------------------------------*/
ULONG num;

ULONG* gregColors;
ULONG* cregColors;

ULONG wbColors[32*3];

ULONG numAlloc;

struct BitMap* bm;

struct TagItem tags[] =
{
	{PDTA_CRegs, (ULONG)&cregColors},
	{PDTA_GRegs, (ULONG)&gregColors},
	{PDTA_NumColors, (ULONG)&num},
	{PDTA_DestBitMap, (ULONG)&bm},
	{PDTA_NumAlloc, (ULONG)&numAlloc},
	{TAG_END, TAG_END}
};

int GfxCopyToScreen(void)
{
	int result = -1;

	struct Screen* wbScreen = LockPubScreen(NULL);

	Object* o = NewDTObject("Neon-City-32.iff", DTA_GroupID, GID_PICTURE, PDTA_Remap, TRUE, PDTA_Screen, (ULONG)wbScreen, TAG_END);

	if (NULL != o)
	{
		DoDTMethod(o, NULL, NULL, DTM_PROCLAYOUT,NULL,TRUE);

		ULONG r = GetDTAttrsA(o, tags);
	
		printf("num alloc = %lx\n", numAlloc);

		const ULONG width = GetBitMapAttr(bm, BMA_WIDTH);
		const ULONG height = GetBitMapAttr(bm, BMA_HEIGHT);
		const ULONG depth  = GetBitMapAttr(bm, BMA_DEPTH);

		struct RastPort* rp = ScreenGetRastPort();

		BltBitMapRastPort(bm,0,0, rp, 0, 0, width, height, 0xC0);

		struct Screen* scr = (struct Screen*)ScreenGetAddress();
	

		ULONG* cc1 = cregColors;

		GetRGB32(wbScreen->ViewPort.ColorMap, 0, 32, &wbColors[0]);
		ULONG* cc = wbColors;

		for (int i = 0; i < num; ++i)
		{
			ULONG r = *cc1++;
			ULONG g = *cc1++;
			ULONG b = *cc1++;

			ULONG r1 = *cc++;
			ULONG g1 = *cc++;
			ULONG b1 = *cc++;

			SetRGB32(&scr->ViewPort, i, r1 , g1, b1);

			//printf("(%8lx,%8lx,%8lx) (%8lx,%8lx,%8lx)\n",r,g,b,r1,g1,b1);
		}


		DisposeDTObject(o);
	}

	UnlockPubScreen(NULL, wbScreen);

	return result;
}

/*--------------------------------------------------------------------------*/

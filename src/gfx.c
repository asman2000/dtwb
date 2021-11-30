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
//struct ColorRegister* cregs;
ULONG* colors;

ULONG* cregColors;

ULONG wbColors[32*3];

ULONG numAlloc;

struct BitMap* bm;

struct TagItem tags[] =
{
	//{PDTA_ColorRegisters, (ULONG)&cregs},
	{PDTA_CRegs, (ULONG)&cregColors},
	{PDTA_GRegs, (ULONG)&colors},
	{PDTA_NumColors, (ULONG)&num},
	{PDTA_DestBitMap, (ULONG)&bm},
	{PDTA_NumAlloc, (ULONG)&numAlloc},
	{TAG_END, TAG_END}
};

// struct TagItem screenTags[] =
// {
// 	{DTA_GroupID, GID_PICTURE},
// 	{PDTA_Remap, TRUE},
// 	{PDTA_Screen, 0},
// 	{TAG_END, TAG_END}
// };

int GfxCopyToScreen(void)
{
	int result = -1;

	struct Screen* screen = LockPubScreen(NULL);
	//SetTag(screenTags, PDTA_Screen, (ULONG)screen);

	GetRGB32(screen->ViewPort.ColorMap, 0, 32, &wbColors[0]);

	Object* o = NewDTObject("Neon-City-32.iff", DTA_GroupID, GID_PICTURE, PDTA_Remap, TRUE, PDTA_Screen, (ULONG)screen, TAG_END);

	if (NULL != o)
	{
		DoDTMethod(o, NULL, NULL, DTM_PROCLAYOUT,NULL,TRUE);

		ULONG r = GetDTAttrsA(o, tags);
	
		printf("num alloc = %lx\n", numAlloc);

		const ULONG width = GetBitMapAttr(bm, BMA_WIDTH);
		const ULONG height = GetBitMapAttr(bm, BMA_HEIGHT);
		const ULONG depth  = GetBitMapAttr(bm, BMA_DEPTH);
		
		//printf("w = %lu, h = %lu, d = %lu\n", width, height, depth);

		struct RastPort* rp = ScreenGetRastPort();

		BltBitMapRastPort(bm,0,0, rp, 0, 0, width, height, 0xC0);

		// struct BitMap* copyBm = AllocBitMap(width, height, depth, BMF_DISPLAYABLE|BMF_CLEAR, NULL);

		// if (copyBm)
		// {
		// 	BltBitMap(bm, 0, 0, copyBm, 0, 0, width, height, 0xC0, 0xFF, NULL);
		// }

		struct Screen* scr = (struct Screen*)ScreenGetAddress();
	

		ULONG* cc1 = colors;
		ULONG* cc = cregColors;

		for (int i = 0; i < num; ++i)
		{
			//ULONG r = cregs[i].red << 24;
			//ULONG g = cregs[i].green << 24;
			//ULONG b = cregs[i].blue << 24;

			ULONG r = *cc1++;
			ULONG g = *cc1++;
			ULONG b = *cc1++;

			

			ULONG r1 = *cc++;
			ULONG g1 = *cc++;
			ULONG b1 = *cc++;

			SetRGB32CM(scr->ViewPort.ColorMap, i, r , g, b);

			printf("(%8lx,%8lx,%8lx) (%8lx,%8lx,%8lx)\n",r,g,b,r1,g1,b1);
		}


		DisposeDTObject(o);

		//BltBitMapRastPort(copyBm,0,0, rp, 0, 0, width, height, 0xC0);
		//FreeBitMap(copyBm);
	}

	UnlockPubScreen(NULL, screen);

	return result;
}

/*--------------------------------------------------------------------------*/

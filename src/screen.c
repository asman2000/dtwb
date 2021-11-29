#include "screen.h"

#include "bitmap.h"
#include "utils.h"

#include <dos/dos.h>
#include <intuition/intuition.h>


#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/utility.h>

/*--------------------------------------------------------------------------*/

static struct Screen* scr = NULL;

static struct BitMap* bitmap = NULL; 

static struct TagItem tags[] =
{
	{SA_BitMap, 0},
	{SA_Width, 0},
	{SA_Height, 0},
	{SA_Depth, 0},
	{SA_DisplayID, 0},
	{SA_Left, 0},
	{SA_Top, 0},
	{SA_Type, CUSTOMSCREEN | CUSTOMBITMAP},
	{SA_Quiet, TRUE},
	{TAG_DONE, TAG_END},
};

static struct Dimension wbDim;

static void ScreenGetWbDimensions(void);

/*--------------------------------------------------------------------------*/

int ScreenOpen(void)
{
	ScreenGetWbDimensions();

	bitmap = BitmapDisplayable(&wbDim);

	if (NULL == bitmap)
	{
		return RETURN_FAIL;
	}

	
	SetTag(tags, SA_BitMap, (ULONG)bitmap); 
	SetTag(tags, SA_Width, wbDim.width);
	SetTag(tags, SA_Height, wbDim.height);
	SetTag(tags, SA_Depth, wbDim.depth);
	SetTag(tags, SA_DisplayID, wbDim.displayId);

	scr  = OpenScreenTagList(NULL, tags);

	if (NULL == scr)
	{
		return RETURN_FAIL;
	}


	return RETURN_OK;
}

/*--------------------------------------------------------------------------*/

static void ScreenGetWbDimensions(void)
{
	struct Screen* screen = LockPubScreen(NULL);

	const struct BitMap* bm = &screen->BitMap;
	wbDim.width = GetBitMapAttr(bm, BMA_WIDTH);
	wbDim.height = GetBitMapAttr(bm, BMA_HEIGHT);
	wbDim.depth = GetBitMapAttr(bm, BMA_DEPTH);
	wbDim.displayId = GetVPModeID(&screen->ViewPort);

	UnlockPubScreen(NULL, screen);
}

/*--------------------------------------------------------------------------*/

void ScreenClose(void)
{
	if (scr)
	{
		CloseScreen(scr);
		scr = NULL;
	}
	
	BitmapFree(bitmap);
	bitmap = NULL;
}

/*--------------------------------------------------------------------------*/

ULONG ScreenGetAddress(void)
{
	return (ULONG)scr;
}

/*--------------------------------------------------------------------------*/

struct RastPort* ScreenGetRastPort(void)
{
	return &scr->RastPort;
}

/*--------------------------------------------------------------------------*/

#include "window.h"

#include "input.h"


#include "screen.h"
#include "utils.h"

#include <dos/dos.h>
#include <intuition/intuition.h>

#include <proto/exec.h>
#include <proto/intuition.h>



/*--------------------------------------------------------------------------*/

static struct Window* win = NULL;

static ULONG windowSignal;

/*--------------------------------------------------------------------------*/

void WindowProcessInputs(void)
{
	const ULONG signals = Wait(windowSignal | SIGBREAKF_CTRL_C);

	if (signals & SIGBREAKF_CTRL_C)
	{
		InputSetEscKey();
		return;
	}

	if (signals & windowSignal)
	{
		struct IntuiMessage *msg;

		while (TRUE)
		{
			ULONG msgClass;
			UWORD msgCode;
			msg = (struct IntuiMessage*)GetMsg(win->UserPort);

			if (NULL == msg)
			{
				break;
			}

			msgClass = msg->Class;
			msgCode = msg->Code;
			
			ReplyMsg((struct Message*)msg);

			if (msgClass == IDCMP_RAWKEY)
			{
				InputSetKeys(msgCode);
			}
		}
	}
}
/*--------------------------------------------------------------------------*/

static struct TagItem tags[] =
{
	{WA_Left, 0},
	{WA_Top, 0},
	{WA_InnerWidth, 0},
	{WA_InnerHeight, 0},
	{WA_Activate, TRUE},
	{WA_GimmeZeroZero, TRUE},
	{WA_RMBTrap, TRUE},
	{WA_IDCMP, IDCMP_RAWKEY},
	{WA_DragBar, TRUE},
	{WA_NoCareRefresh, TRUE},
	{WA_CustomScreen, 0},
	{WA_Borderless, TRUE},
	{WA_Backdrop, TRUE},
	{TAG_END, TAG_END},
};
 
/*--------------------------------------------------------------------------*/

int WindowOpen(void)
{
	struct Screen* scr = (struct Screen*)ScreenGetAddress();

	SetTag(tags, WA_CustomScreen, (Tag)scr);
	SetTag(tags, WA_InnerWidth, (Tag)scr->Width);
	SetTag(tags, WA_InnerHeight, (Tag)scr->Height);

	win = OpenWindowTagList(NULL, tags);

	if (NULL == win)
	{
		return RETURN_FAIL;
	}

	windowSignal = 1L << win->UserPort->mp_SigBit; 

	return RETURN_OK;
}

/*--------------------------------------------------------------------------*/

void WindowClose(void)
{
	if (win)
	{
		CloseWindow(win);
	}
}

/*--------------------------------------------------------------------------*/

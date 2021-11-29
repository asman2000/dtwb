#include "init.h"

#include "input.h"
#include "libs.h"
#include "screen.h"
#include "window.h"


/*--------------------------------------------------------------------------*/

int InitOpen(void)
{
	InputInit();

	int result = LibsOpen();

	if (RETURN_OK == result)
	{
		result = ScreenOpen();
	}

	if (RETURN_OK == result)
	{
		result = WindowOpen();
	}

	return result;
}

/*--------------------------------------------------------------------------*/

void InitClose(void)
{
	WindowClose();
	ScreenClose();
	LibsClose();
}

/*--------------------------------------------------------------------------*/

#include "init.h"

#include "libs.h"
#include "screen.h"


/*--------------------------------------------------------------------------*/

int InitOpen(void)
{
	int result = LibsOpen();

	if (RETURN_OK == result)
	{
		result = ScreenOpen();
	}

	return result;
}

/*--------------------------------------------------------------------------*/

void InitClose(void)
{
	ScreenClose();
	LibsClose();
}

/*--------------------------------------------------------------------------*/

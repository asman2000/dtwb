
#include "gfx.h"
#include "init.h"
#include "input.h"
#include "window.h"
#include "types.h"


/*--------------------------------------------------------------------------*/

int main(void)
{
	int result = InitOpen();

	if (RETURN_OK == result)
	{
		GfxCopyToScreen();

		while (TRUE)
		{
			WindowProcessInputs();

			if (InputIsExitToOsPressed())
			{
				break;
			}
		}
	}

	InitClose();

	return 0;
}

/*--------------------------------------------------------------------------*/

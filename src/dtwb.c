
#include "init.h"
#include "types.h"

#include <proto/dos.h>
/*--------------------------------------------------------------------------*/

int main(void)
{
	int result = InitOpen();

	if (RETURN_OK == result)
	{
		Delay(200);
	}

	InitClose();

	return 0;
}

/*--------------------------------------------------------------------------*/

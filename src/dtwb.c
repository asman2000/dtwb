
#include "init.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

int main(void)
{
	int result = InitOpen();

	if (RETURN_OK == result)
	{
	}

	InitClose();

	return 0;
}

/*--------------------------------------------------------------------------*/

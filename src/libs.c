#include "libs.h"

#include "types.h"

#include <proto/exec.h> 

/*--------------------------------------------------------------------------*/

struct GfxBase* GfxBase = NULL;
struct IntuitionBase* IntuitionBase = NULL;
struct Library* UtilityBase = NULL;
struct Library* DataTypesBase = NULL;


static const char* gfxName = "graphics.library";
static const char* itnName = "intuition.library";
static const char* utlName = "utility.library";
static const char* dtpName = "datatypes.library";
/*--------------------------------------------------------------------------*/

int LibsOpen(void)
{
	GfxBase = (struct GfxBase*)OpenLibrary(gfxName, 36);

	if (NULL == GfxBase)
	{
		return RETURN_FAIL;
	}

	IntuitionBase = (struct IntuitionBase*)OpenLibrary(itnName, 36);

	if (NULL == IntuitionBase)
	{
		return RETURN_FAIL;
	}

	UtilityBase = OpenLibrary(utlName, 0);

	if (NULL == UtilityBase)
	{
		return RETURN_FAIL;
	}

	DataTypesBase = OpenLibrary(dtpName,0);

	if (NULL == DataTypesBase)
	{
		return RETURN_FAIL;
	}


	return RETURN_OK;
}

/*--------------------------------------------------------------------------*/

void LibsClose(void)
{
	CloseLibrary(DataTypesBase);
	CloseLibrary(UtilityBase);
	CloseLibrary((struct Library*)IntuitionBase);
	CloseLibrary((struct Library*)GfxBase);
}

/*--------------------------------------------------------------------------*/

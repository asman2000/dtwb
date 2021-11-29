#ifndef DTWB_TYPES_H
#define DTWB_TYPES_H
/*--------------------------------------------------------------------------*/
#include <exec/types.h>

#include <dos/dos.h>
#include <utility/tagitem.h>

struct Dimension
{
	ULONG width;
	ULONG height;
	ULONG depth;
	ULONG displayId;
};

/*--------------------------------------------------------------------------*/
#endif /* DTWB_TYPES_H */

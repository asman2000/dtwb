#include "utils.h"

#include <proto/utility.h>

/*--------------------------------------------------------------------------*/

void SetTag(struct TagItem* tags, Tag name, Tag value )
{
	struct TagItem* item = FindTagItem(name, tags);

	if (item)
	{
		item->ti_Data = value;
	}
}

/*--------------------------------------------------------------------------*/

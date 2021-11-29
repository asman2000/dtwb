#ifndef DTWB_INPUT_H
#define DTWB_INPUT_H
/*--------------------------------------------------------------------------*/

#include "types.h"

void InputInit(void);

void InputSetKeys(UWORD msgCode);
BOOL InputIsExitToOsPressed(void);

void InputSetEscKey(void);

/*--------------------------------------------------------------------------*/
#endif /* DTWB_INPUT_H */

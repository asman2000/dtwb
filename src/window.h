#ifndef DTWB_WINDOW_H
#define DTWB_WINDOW_H
/*--------------------------------------------------------------------------*/

int WindowOpen(void);
void WindowClose(void);

void WindowProcessInputs(void);

struct RastPort* WindowGetRastPort(void);
/*--------------------------------------------------------------------------*/
#endif /* DTWB_WINDOW_H */

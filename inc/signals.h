#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <signal.h>
int handle_sigaction(void);
void sigquit_handler(int);

#endif

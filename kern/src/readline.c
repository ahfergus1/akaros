#ifdef __SHARC__
#pragma nosharc
#endif

#include <error.h>
#include <stdio.h>

#define BUFLEN 1024
// zra: used only by monitor.c.
static char RACY (RO NT buf)[BUFLEN];

char *
readline(const char *prompt, ...)
{
	int i, c, echoing;
	va_list ap;

	va_start(ap, prompt);
	if (prompt != NULL)
		vcprintf(prompt, ap);
	va_end(ap);

	i = 0;
	echoing = iscons(0);
	while (1) {
		c = getchar();
		if (c < 0) {
			cprintf("read error: %e\n", c);
			return NULL;
		} else if (c >= ' ' && i < BUFLEN-1) {
			if (echoing)
				cputchar(c);
			buf[i++] = c;
		} else if (c == '\b' && i > 0) {
			if (echoing)
				cputchar(c);
			i--;
		} else if (c == '\n' || c == '\r') {
			if (echoing)
				cputchar(c);
			buf[i] = 0;
			return buf;
		}
	}
}


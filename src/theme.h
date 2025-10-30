/* theme.h – K&R/C89, Plan 9 headers only */

#ifndef _THEME_H_
#define _THEME_H_

typedef struct Theme Theme;
struct Theme {
	ulong bg;
	ulong fg;
	ulong border;
	ulong selbg;
	ulong selfg;
	ulong mouse;
};

void	themedefaults(Theme*);
int	loadtheme(Theme*, char*, char*);   /* (t, themename, user) */
int	parsehexrgb(char*, ulong*);

#endif

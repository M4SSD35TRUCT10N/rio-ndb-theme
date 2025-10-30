/* theme.c – K&R/C89, no C99, simple NDB-style parser */

#include <u.h>
#include <libc.h>
#include <bio.h>
#include "theme.h"

static int	readriofile(Theme*, char*, char*);
static int	matchservice(char*);
static int	matchtheme(char*, char*);
static void	parseline(Theme*, char*);
static void	applykv(Theme*, char*, char*);

int
parsehexrgb(s, p)
	char *s;
	ulong *p;
{
	ulong v;
	int i, d;

	if(s == nil)
		return -1;
	if(s[0] == '#')
		s++;

	v = 0;
	for(i = 0; i < 6 && s[i]; i++){
		d = s[i];
		if(d >= '0' && d <= '9')
			d -= '0';
		else if(d >= 'a' && d <= 'f')
			d = d - 'a' + 10;
		else if(d >= 'A' && d <= 'F')
			d = d - 'A' + 10;
		else
			return -1;
		v = (v<<4) | d;
	}
	if(i != 6)
		return -1;

	*p = v;
	return 0;
}

void
themedefaults(t)
	Theme *t;
{
	/* Setze hier die existierenden rio-Defaults (Beispielwerte): */
	t->bg     = 0xFFFFFF;
	t->fg     = 0x000000;
	t->border = 0x999999;
	t->selbg  = 0x3875D6;
	t->selfg  = 0xFFFFFF;
	t->mouse  = 0x000000;
}

static int
matchservice(line)
	char *line;
{
	char *p;

	p = strstr(line, "service=rio");
	if(p == nil)
		return 0;
	if(p > line && p[-1] != ' ' && p[-1] != '\t' && p[-1] != '\n')
		return 0;
	return 1;
}

static int
matchtheme(line, themename)
	char *line;
	char *themename;
{
	char *p;
	char buf[128];
	int n;

	if(themename == nil || themename[0] == 0)
		return 1;

	p = strstr(line, "theme=");
	if(p == nil)
		return 0;

	p += 6;
	n = 0;
	while(p[n] && p[n] != ' ' && p[n] != '\t' && p[n] != '\n')
		n++;
	if(n >= (int)sizeof buf)
		n = sizeof buf - 1;

	memmove(buf, p, n);
	buf[n] = 0;

	if(strcmp(buf, themename) == 0)
		return 1;
	return 0;
}

static void
applykv(t, key, val)
	Theme *t;
	char *key;
	char *val;
{
	ulong v;

	if(key == nil || val == nil)
		return;
	if(parsehexrgb(val, &v) < 0)
		return;

	if(strcmp(key, "bg") == 0)
		t->bg = v;
	else if(strcmp(key, "fg") == 0)
		t->fg = v;
	else if(strcmp(key, "border") == 0)
		t->border = v;
	else if(strcmp(key, "selbg") == 0)
		t->selbg = v;
	else if(strcmp(key, "selfg") == 0)
		t->selfg = v;
	else if(strcmp(key, "mouse") == 0)
		t->mouse = v;
}

static void
parseline(t, s)
	Theme *t;
	char *s;
{
	char *p, *k, *v;

	p = s;
	for(;;){
		while(*p == ' ' || *p == '\t')
			p++;
		if(*p == 0 || *p == '#')
			break;

		k = p;
		while(*p && *p != '=' && *p != ' ' && *p != '\t' && *p != '\n')
			p++;
		if(*p != '=')
			break;

		*p++ = 0;
		v = p;
		while(*p && *p != ' ' && *p != '\t' && *p != '\n')
			p++;
		if(*p){
			*p = 0;
			p++;
		}
		applykv(t, k, v);
	}
}

static int
readriofile(t, themename, path)
	Theme *t;
	char *themename;
	char *path;
{
	Biobuf *b;
	char *line, *p;
	int ok, cont;
	char acc[1024];

	b = Bopen(path, OREAD);
	if(b == nil)
		return 0;

	ok = 0;
	cont = 0;
	acc[0] = 0;

	while((line = Brdstr(b, '\n', 1)) != nil){
		p = line + strlen(line);

		if(p > line && p[-1] == '\\'){
			p[-1] = ' ';
			if(strlen(acc) + strlen(line) + 1 < sizeof acc)
				strcat(acc, line);
			free(line);
			cont = 1;
			continue;
		}

		if(cont){
			if(strlen(acc) + strlen(line) + 1 < sizeof acc)
				strcat(acc, line);
			free(line);
			line = strdup(acc);
			acc[0] = 0;
			cont = 0;
		}

		if(matchservice(line) && matchtheme(line, themename)){
			parseline(t, line);
			ok = 1;
			free(line);
			break;
		}
		free(line);
	}
	Bterm(b);
	return ok;
}

int
loadtheme(t, themename, user)
	Theme *t;
	char *themename;
	char *user;
{
	char path[256];

	if(user && user[0]){
		snprint(path, sizeof path, "/usr/%s/lib/ndb/rio", user);
		if(readriofile(t, themename, path))
			return 1;
	}
	if(readriofile(t, themename, "/lib/ndb/rio"))
		return 1;

	return 0;
}

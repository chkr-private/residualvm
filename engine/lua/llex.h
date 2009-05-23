/*
** $Id$
** Lexical Analizer
** See Copyright Notice in lua.h
*/

#ifndef llex_h
#define llex_h

#include "engine/lua/lobject.h"
#include "engine/lua/lzio.h"

#define MAX_IFS 5

// "ifstate" keeps the state of each nested $if the lexical is dealing with.

struct ifState {
	int32 elsepart;  // true if its in the $else part
	int32 condition;  // true if $if condition is true
	int32 skip;  // true if part must be skipped
};

typedef struct LexState {
	int32 current;  // look ahead character
	zio *lex_z;  // input stream
	int32 linenumber;  // input line counter
	int linelasttoken;  /* line where last token was read */
	int lastline;  /* last line wherein a SETLINE was generated */
	int32 iflevel;  // level of nested $if's (for lexical analysis)
	ifState ifstate[MAX_IFS];
} LexState;

void luaX_init();
void luaX_setinput(ZIO *z);
char *luaX_lasttoken();

#endif

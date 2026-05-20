#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include "Scanner.h"

#define MAXTOKEN 64

extern char name[MAXTOKEN];
extern char out[1000];

void dcl(void);
void dirdcl(void);

#endif

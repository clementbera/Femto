#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int numTokens;
	char **tokens;
} Tokens;

Tokens * tokenizefile(FILE* f);
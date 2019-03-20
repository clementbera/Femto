#include "../types.h"
#include "Tokenizer.h" 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TokenBufferSize 2000
#define StringBufferSize 100

#define HardSeparatorsSize 3
#define SeparatorsSize 7
#define BinaryCharactersSize 11

char hardSeparators[] = {' ','\t','\n'};
char separators[] = {',',';','{','}','(',')','.'};
char binaryCharacters[]  = {'+','-','*','/','&','|','<','>','^','=','!',};
char stringToken = '"';
char *lineCommentToken = "//";
char *multiLineCommentTokenStart = "/*";
char *multiLineCommentTokenEnd = "*/";

int inList(char c, char* list, int length){
	for(int i=0;i<length;i++){
		if(list[i]==c){return 1;}
	}
	return 0;
}

int bothEqualsSize2(char *str1, char *str2){
	return (str1[0] == str2[0]) & (str1[1] == str2[1]);
}

int parseToken(FILE* f, char *stringBuffer){
	int strPos = 0;
	int current = fgetc(f);
	if(current == EOF){return 0;}
	while(inList(current,hardSeparators,HardSeparatorsSize)){
		current = fgetc(f);
		if(current == EOF){return 0;}
	}
	// String
	printf("%c ",current);
	if(stringToken == current){
		stringBuffer[strPos++]= current;
		current = fgetc(f);
		while(stringToken != current){
			stringBuffer[strPos++]= current;
			current = fgetc(f);
		}
		stringBuffer[strPos++]= current;
		return strPos;
	}
	if(inList(current,binaryCharacters,BinaryCharactersSize)){
		// Binary token
		while(inList(current,binaryCharacters,BinaryCharactersSize)){
			stringBuffer[strPos++]= current;
			current = fgetc(f);
		}
		return strPos;
	}
	// Separator
	if(inList(current,separators,SeparatorsSize)){
		//Separator
		stringBuffer[strPos++]= current;
		return strPos;
	}
	// Default token
	while(!(inList(current,hardSeparators,HardSeparatorsSize) 		
		| inList(current,separators,SeparatorsSize)
		| inList(current,binaryCharacters,BinaryCharactersSize))){
		stringBuffer[strPos++]= current;
		current = fgetc(f);
	}
	ungetc(current,f);
	return strPos;
}

void addString(int strSize, char *stringBuffer, char **tokenBuffer, Tokens *tokens){
	char *newString = (char *) malloc((strSize + 1) * sizeof(char));
	memcpy(newString, stringBuffer, strSize);
	tokenBuffer[tokens->numTokens++] = newString;
	printf("%s %i \n",newString,strSize);
	if(tokens->numTokens > TokenBufferSize){
		printf("token buffer overflow");
		exit(-1);
	}
}

Tokens * tokenizefile(FILE* f){
	Tokens *tokens = (Tokens *) malloc(sizeof(Tokens));
	char *stringBuffer = (char *) malloc(StringBufferSize);
	char **tokenBuffer = (char **) malloc(TokenBufferSize*sizeof(char *));
	int ret = 1;
	while(ret != 0){
		ret = parseToken(f, stringBuffer);
		if (ret != 0){
			if (ret == 2) {
				// Comments management
				if(bothEqualsSize2(stringBuffer,lineCommentToken)){
					int current = fgetc(f);
					while(current != '\n'){current = fgetc(f);}
				} else if (bothEqualsSize2(stringBuffer,multiLineCommentTokenStart)){
					int ret2 = ret;
					while(!((ret2 == 2) & bothEqualsSize2(stringBuffer,multiLineCommentTokenEnd))){
						ret2 = parseToken(f,stringBuffer);}
				} else {
					addString(ret,stringBuffer,tokenBuffer,tokens);
				}
			} else {
				addString(ret,stringBuffer,tokenBuffer,tokens);
			}
		}
	}
	tokens->tokens = realloc(tokenBuffer,tokens->numTokens*sizeof(char *));
	free(stringBuffer);
	return tokens;	
}

/* TEST
int main(){
	char *path = (char *)malloc(100);
    strcpy(path, KERNELPATH);
	strcat(path,"/Core/Behaviors/Behavior.femto");
	FILE * f = fopen(path, "r");
	Tokens * tokens = tokenizefile(f);
	fclose(f);
	for (int i = 0; i<tokens->numTokens; i++){
		printf("%i %s\n",i,tokens->tokens[i]);
	}
}
*/


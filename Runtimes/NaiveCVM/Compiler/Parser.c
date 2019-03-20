#include "../Types.h"
#include "AST.h"
#include "Tokenizer.h" 
#include "../MemoryManagementCommon.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define InstructionBufferSize 80

ASTClass * parseFileNamed(char *localPath);

// Class pattern parsing

UInt8 parseFmt(char *fmt){
	if (strcmp(fmt, "fixedClass") == 0) {return FixedFmt;}
	if (strcmp(fmt, "arrayClass") == 0) {return ArrayFmt;}
	if (strcmp(fmt, "nativeClass") == 0) {return NativeFmt;}
	if (strcmp(fmt, "ImmediateClass") == 0) {return ImmediateFmt;}
	printf("Non recognized class fmt for %s", *tokens++);
	exit(-1);
}

char ** parseArgs(Tokens *tokens,int *tokenIndex, int *numArgs){
	assert(!strCmp(tokens->tokens[*tokenIndex++],"("));
	current = tokens->tokens[*tokenIndex];
	// scan for num of inst vars
	while(strCmp(current,")")){
		*numInstVars++;
		current = tokens->tokens[*tokenIndex+(2*(*numInstVars))];
	}
	char ** instVarNames = (char **) malloc(*numInstVars*sizeof(char *));
	current = tokens->tokens[*tokenIndex++];
	UInt16 numIVs=0;
	// parse inst vars
	while(strCmp(current,")")){
		instVarNames[numIVs++]= strcpy(malloc(strlen(current)*sizeof(char)), current);
		current = tokens->tokens[*tokenIndex++];
		current = tokens->tokens[*tokenIndex++];
	}
	return instVarNames;
}

ASTClass * parseClassPattern(Tokens *tokens,int *tokenIndex){
	ASTClass *class = (ASTClass *) malloc(sizeof(ASTClass));
	class->type = ASTClassType;
	class->class = (ASTMetaClass *) malloc(sizeof(ASTMetaClass));
	class->class->type = ASTMetaClassType;
	char *current = tokens->tokens[*tokenIndex++];
	// abstract
	if (strcmp(current,"abstract")){
		class->abstract = 1;
		current = tokens->tokens[*tokenIndex++];
	}
	// fmt
	class->fmt = parseFmt(current);
	// name
	class->name = tokens->tokens[*tokenIndex++];
	// inst vars
	class->instVarNames = parseArgs(tokens, tokenIndex, &(class->numInstVars));
	// superclass
	current = tokens->tokens[*tokenIndex++];
	if (!strCmp(current,"extends")){
		class->superclassName = "Object";
	} else {
		class->superclassName = tokens->tokens[*tokenIndex++];
	}
	assert(!strCmp(tokens->tokens[*tokenIndex++],"{"));
	return class;
}

// Inner function parsing

ASTNode * parseVirtualCallStatement(Tokens *tokens,int *tokenIndex){
	UInt16 numVCalls = scanChain(Tokens *tokens,int *tokenIndex);
	if (!numVCalls){
		return parseVariable
	}
	return (ASTNode *) malloc(sizeof(ASTNode));
}

ASTNode * parseIfStatement(Tokens *tokens,int *tokenIndex){
	return (ASTNode *) malloc(sizeof(ASTNode));
}

ASTNode * parseForStatement(Tokens *tokens,int *tokenIndex){
	return (ASTNode *) malloc(sizeof(ASTNode));
}

ASTNode * parseReturnStatement(Tokens *tokens,int *tokenIndex){
	return (ASTNode *) malloc(sizeof(ASTNode));
}

ASTNode * parseStatement(Tokens *tokens,int *tokenIndex){
	// What are the posibilities? Starts with if, for, return or v-call (binary or not).
	char *current = tokens->tokens[*tokenIndex];
	if (!strCmp(current,"if")){
		return parseIfStatement(Tokens *tokens,int *tokenIndex);
	} else if (!strCmp(current,"for")){
		return parseForStatement(Tokens *tokens,int *tokenIndex);
	} else if (!strCmp(current,"return")){
		return parseReturnStatement(Tokens *tokens,int *tokenIndex);
	} else {
		return parseVirtualCallStatement(Tokens *tokens,int *tokenIndex);
	}
}

// Function parsing

void parseFunctionPattern(Tokens *tokens,int *tokenIndex, ASTFunction *func){
	// instrinsic(X) binary function + arg{}
	// abstract function(x,y);
	// binary, intrinsic and abstract are before function.
	// binary change arg parsing, abstract there is no body.
	char *current = tokens->tokens[*tokenIndex++];
	while (strCmp(current,"function")){
		if(!strCmp(current,"binary"){
			func->binary = 1;
		} else if (!strCmp(current,"intrinsic")){
			assert(!strCmp(tokens->tokens[*tokenIndex++],"("));
			func->intrinsic = (UInt16) strtoumax(tokens->tokens[*tokenIndex++], NULL, 10);
			assert(!strCmp(tokens->tokens[*tokenIndex++],")"));
		} else if (!strCmp(current,"abstract")){
			func->abstract = 1;
		}
		current = tokens->tokens[*tokenIndex++];
	}
	current = tokens->tokens[*tokenIndex++];
	func->functionName = strcpy(malloc(strlen(current)*sizeof(char)), current);
	if (func->binary){
		current = tokens->tokens[*tokenIndex++];
		func->numArgs = 1;
		func->argNames = (char **) malloc(sizeof(char *));
		func->argNames[0] = strcpy(malloc(strlen(current)*sizeof(char)), current);
	} else {
		class->argNames = parseArgs(tokens, tokenIndex, &(class->numArgs));
	}
	if (func->abstract){
		assert(!strCmp(tokens->tokens[*tokenIndex],";"));
	} else {
		assert(!strCmp(tokens->tokens[*tokenIndex],"{}"));
	}
}

void parseFunctionTemps(Tokens *tokens,int *tokenIndex, ASTFunction *func){
	if (strCmp(tokens->tokens[*tokenIndex],"var")){return;}
	*tokenIndex++;
	function->numTemps++;
	current = tokens->tokens[(*tokenIndex) + 1];
	while(strCmp(current,";"){
		function->numTemps++;
		current = tokens->tokens[(*tokenIndex) + 1 + (2*function->numTemps)];
	}
	function->tempNames = (char **) malloc(function->numTemps * sizeof(char *));
	int numTemps = 0;
	current = tokens->tokens[*tokenIndex++];
	function->tempNames[numTemps++]= strcpy(malloc(strlen(current)*sizeof(char)), current);
	current = tokens->tokens[*tokenIndex++];
	while(strCmp(current,";"){
		current = tokens->tokens[*tokenIndex++];
		function->tempNames[numTemps++]= strcpy(malloc(strlen(current)*sizeof(char)), current);
		current = tokens->tokens[*tokenIndex++];
	}
}

ASTFunction * parseFunctionStatement(Tokens *tokens,int *tokenIndex){
	ASTFunction *func = (ASTFunction *) malloc(sizeof(ASTFunction));
	func->type=ASTFunctionType;
	parseFunctionPattern(tokens, tokenIndex, func);
	if (func->abstract){
		*tokenIndex++;
		return func;
	}
	parseFunctionTemps(tokens, tokenIndex, func);
	ASTNode *instructionBuffer = (ASTNode *) malloc(InstructionBufferSize*sizeof(ASTNode *));
	while(!strCmp(tokens->tokens[current],"}"){
		instructionBuffer[func->numInstructions++] = parseStatement(tokens,&current);
	}
	function->instruction = (ASTNode *) realloc(instructionBuffer,function->numInstructions * sizeof(ASTNode *));
	return func;
}

// Class side parsing

void parseClassSideStatement(Tokens *tokens,int *tokenIndex,ASTMetaClass *astMetaClass){
	*tokenIndex++;
	// inst vars
	astMetaClass->instVarNames = parseArgs(tokens, tokenIndex, &(astMetaClass->numInstVars));
	assert(!strCmp(tokens->tokens[*tokenIndex++],"{"));
	while(!strCmp(tokens->tokens[current],"}"){
		astMetaClass->functions[astMetaClass->numFunctions++] = parseFunctionStatement(tokens,tokenIndex);
	}
}

// General parsing

void freeTokens(Tokens *tokens){
	for(int i=0;i<tokens->numTokens;i++){free(tokens->tokens[i]);}
	free(tokens);
}

void parseClassStatement(Tokens *tokens,int *tokenIndex,ASTClass *astClass){
	if (!strCmp(tokens->tokens[current],"classSide"){
		return parseClassSideStatement(tokens,tokenIndex,astClass->class);
	}
	astClass->functions[astClass->numFunctions++] = parseFunctionStatement(tokens,tokenIndex);
}

ASTClass * parseFile(FILE *f){
	Tokens * tokens = tokenizefile(f);
	int current = 0;
	ASTClass * astClass = parseClassPattern(tokens,&current);
	while(!strCmp(tokens->tokens[current],"}"){
		parseClassStatement(tokens,&current,astClass);
	}
	freeTokens(tokens);
	return astClass;
}

ASTClass * parseFileNamed(char *localPath){
	char *fullPath = (char *)malloc(100);
    strcpy(fullPath, KERNELPATH);
	strcat(fullPath,localPath);
	FILE * f = fopen(fullPath, "r");
	ASTClass * class = parseFile(f)
	fclose(f);
	return class;
}

/* Testing

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
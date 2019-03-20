#define FunctionScopeIndex 0;
#define InstVarScopeIndex 1;
#define GlobalScopeIndex 2;

typedef struct scope {
	char type;
	struct scope *nextScope;
} Scope;

typedef struct functionScope {
	char type;
	Scope *nextScope;
	UInt8 numArgs;
	UInt8 numTemps;
	char **argNames;
	char **tempNames;
} FunctionScope;

typedef struct instVarScope {
	char type;
	Scope *nextScope;
	UInt16 numInstVars;
	char **instVarNames;
} InstVarScope;

typedef struct globalScope {
	char type;
	Scope *nextScope;
	UInt16 numGlobals;
	Op *globals;
} GlobalScope;

FunctionScope *createScope(ASTFunction *func, UInt16 numInstVars, char **instVarNames, UInt16 numGlobals, Op *globals){
	
	GlobalScope *gScope = (GlobalScope *)malloc(sizeof(GlobalScope));
	gScope->type = GlobalScopeIndex;
	gScope->numGlobals = numGlobals;
	gScope->globals = globals;
	
	InstVarScope *ivScope = (InstVarScope *)malloc(sizeof(InstVarScope));
	ivScope->type = InstVarScopeIndex;
	ivScope->numInstVars = numInstVars;
	ivScope->instVarNames = instVarNames;
	ivScope->nextScope = gScope;
	
	FunctionScope *funcScope = (FunctionScope *)malloc(sizeof(FunctionScope));
	funcScope->type = FunctionScopeIndex;
	funcScope->numArgs = func->numArgs;
	funcScope->numTemps = func->numTemps;
	funcScope->argNames = func->argNames;
	funcScope->tempNames = func->tempNames;
	funcScope->nextScope = ivScope;
	
	return funcScope;
}

ASTNode *lookupScope(char *varName,Scope *scope) {
	
}

ASTNode * nodeForName(char *varName, FunctionScope * funcScope){
	ASTNode *res = NULL;
	Scope *scope = (Scope *)funcScope;
	while((res = lookupScope(varName,scope)) == NULL){
		scope = scope->nextScope;
		if (scope==0){printf("Semantic analysis failed"); exit(-1);}
	}
	return res;
}

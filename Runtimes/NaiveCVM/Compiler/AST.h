#define ASTClassType 0;
#define ASTMetaClass 1;
#define ASTFunction 2;
#define ASTCall 3;
#define ASTTemp 4;
#define ASTInstanceVariable 5;
#define ASTGlobal 6;
#define ASTThis 7;
#define ASTIf 8;
#define ASTFor 9;
#define ASTArg 10;

typedef struct {
	UInt8 type;
} ASTNode;

typedef struct {
	UInt8 type;
	UInt16 numFunctions;
	UInt16 numInstVars;
	ASTFunction *functions;
	char **instVarNames;
} ASTMetaClass;

typedef struct {
	UInt8 type;
	UInt16 numFunctions;
	UInt16 numInstVars;
	ASTFunction *functions;
	char **instVarNames;
	char *name;
	UInt8 fmt;
	UInt8 abstract;
	char *superclassName;
	ASTMetaClass *class;
} ASTClass;

typedef struct {
	UInt8 type;
	UInt8 numTemps;
	UInt8 numArgs;
	UInt8 abstract;
	UInt8 binary;
	UInt16 intrinsic;
	UInt16 numInstructions;
	char *functionName;
	char **argNames;
	char **tempNames;
	ASTNode *instructions;
} ASTFunction;

typedef struct {
	UInt8 type;
	UInt8 numArgs;
	char *functionName;
	ASTNode* receiver;
	ASTNode* arguments;
} ASTCall;

typedef struct {
	UInt8 type;
	UInt16 numTrueInstructions;
	UInt16 numFalseInstructions;
	ASTNode *conditionInstruction;
	ASTNode **trueInstructions;
	ASTNode **falseInstructions;
} ASTIf;

typedef struct {
	UInt8 type;
	ASTNode *initInstruction;
	ASTNode *exitInstruction;
	ASTNode *incrInstruction;
	UInt16 numInstructions;
	ASTNode **bodyInstructions;
} ASTFor;

typedef struct {
	UInt8 type;
	char *varName;
} ASTIf;

typedef struct {
	UInt8 type;
	char *varName;
} ASTArg;

typedef struct {
	UInt8 type;
	char *varName;
} ASTTemp;

typedef struct {
	UInt8 type;
	char *varName;
} ASTInstanceVariable;

typedef struct {
	UInt8 type;
	char *varName;
} ASTGlobal;

typedef struct {
	UInt8 type;
	UInt8 isSuper;
} ASTThis;
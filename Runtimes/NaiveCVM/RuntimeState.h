#include "types.h"

typedef struct {
	Op firstOp;
	UIntP freeStart;
	UIntP gcThreshold;
	UIntP memoryLimit; 
	Op classTable; 
} RuntimeState; 

RuntimeState runtime;
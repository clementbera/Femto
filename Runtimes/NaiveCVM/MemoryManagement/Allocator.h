#include "types.h"
#include "headerAccess.h"
#include "ObjectAccess.h"

// This is in header file to be inlined & avoid macro to keep type checks.

Op allocateObjectForClass(Op class){
	UInt8 fmt = fetchFormat(op);
	UInt16 classIndex = ensureClassIndex(class);
	switch(fmt){
		case FixedFmt:
		return allocateObject(fmt,)
	}
}

void maybeGC(UIntP totalSizeInBytes){
	if ((runtimeState->freeStart + totalSizeInBytes) > runtimeState->gcThreshold){
		garbageCollect();
		if ((runtimeState->freeStart + totalSizeInBytes) > runtimeState->gcThreshold){
			printf("Out of memory");
			exit(-1);
		}
	}
}

Op allocateObject(UInt8 fmt, UInt16 sizeInP, UInt16 classIndex, UIntP initValue){
	UIntP totalSizeInBytes = (UIntP)((sizeInP << 3) + HeaderSizeInBytes);
	maybeGC(totalSizeInBytes);
	Op newOp = opStartingAt(runtimeState->freeStart);
	runtimeState->freeStart += totalSizeInBytes;
	setHeader(newOp, sizeInP, classIndex);
	for(int i = 0; i < sizeInP, i++){
		storeOop(newOp,(Oop)initValue);
	}
	return newOop;
}

#include "types.h"
#include "ObjectAccess.h"
#include "headerAccess.h"

#define LastUsedEntryIndex 0

#define SuperBehaviorIndex 	0
#define MethodDictIndex 	1
#define InstanceFmtIndex 	2

ensureClassIndex(Op class){
	UInt16 classIndex = fetchOpHash(class)
	if(classIndex = 0){
		SIntP last = unboxSmi(fetchOop(runtime->classTable,LastUsedEntryIndex));
	}
	return classIndex;
}

setInstanceFmt(Op class, UInt16 sizeInP, UInt8 fmt){
	storeOop(class, InstanceFmtIndex, sizeInP << 16 + (fmt << 8) + 1)
}
#include "types.h"
#include "HeaderAccess.h"
#include "ObjectAccess.h"

// Mark-compact

Op objectAfter(Op obj){
	// We abuse the fact that we do not need to read the header
	// With header extension we would need to have a limit ;-)
	return opStartingAt(obj + fetchSizeIn64(obj));
}

void opsDo(void(*)(Op op) iterator){
	Op current = firstObject;
	while(current <= freeStart){
		iterator(current);
		current = objectAfter(current);
	}
}

// Marking 

void mark(){
	// set of roots ?
	
	// stack
	
	// process mark stack
}

// Compacting

void compactAndUnmark(){
	assert(emptyGCStack());
	Op firstMobile = reversePointers();
	updatePointers(firstMobile);
	compactMobileObjectsAndUnmark(firstMobile);
}

Op reversePointers(){
	Op firstMobile = 0;
	Op current = firstObject;
	while(current <= freeStart){
		
		push(gcStack, fetchHeader(current));
		storeHeader(current, );
		
		current = objectAfter(current);
	}
}

// assert

int allUnmarked(){
	
}

// public

void garbageCollect(){
	mark();
	compactAndUnmark();
	assert(allUnmarked());
}

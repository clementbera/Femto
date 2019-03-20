#include "types.h"
#include "HeaderAccess.h"
#include "ObjectAccess.h"
#include <assert.h>

// Special object array indexes

#define NullSpecialIndex 			(UIntP)0;
#define FalseSpecialIndex 			(UIntP)1;
#define TrueSpecialIndex 			(UIntP)2;
#define RuntimeSpecialIndex 		(UIntP)3;

#define SmallIntegerSpecialIndex 	(UIntP)5;
#define ArraySpecialIndex 			(UIntP)6;
#define VirtualCallSpecialIndex 	(UIntP)7;

#define NosuchMethodSpecialIndex 	(UIntP)10;
#define UnknownBytecodeSpecialIndex (UIntP)11;
#define MustBeBooleanSpecialIndex 	(UIntP)12;

#define CharacterTableSpecialIndex 	(UIntP)15;
#define ClassTableSpecialIndex 		(UIntP)16;

#define SpecialObjectArraySize (UInt16)17;

// Accessing

Oop getSpecialObject(int index){
	return fetchOop(runtimeState->firstOop, index);
}

Oop getTrueObject(){
	return getSpecialObject(TrueSpecialIndex);
}

Oop getFalseObject(){
	return getSpecialObject(FalseSpecialIndex);
}

Oop getNullObject(){
	return getSpecialObject(NullSpecialIndex);
}

Oop getSmallIntegerObject(){
	return getSpecialObject(SmallIntegerSpecialIndex);
}

Oop getArrayObject(){
	return getSpecialObject(ArraySpecialIndex);
}

Oop getVirtualCallObject(){
	return getSpecialObject(VirtualCallSpecialIndex);
}
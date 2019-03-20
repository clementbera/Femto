#include "types.h"
#include "HeaderAccess.h"
#include "ObjectAccess.h"
#include "RuntimeState.h"
#include "specialObjects.h"
#include <assert.h>

#define RuntimeSize (UIntP)(100 * 1000 * 1000) //100 Mb
#define RuntimeObjSizeInP (UInt16)2
#define ClassSizeInP (UInt16)5
#define MetaclassSizeInP (UInt16)5

void startUp(char *snapshotPath, char **extensions, char *signature){
	createRuntimeState();
	if (snapshotPath == NULL){
		createInitialObjects();
	} else {
		printf("TODO!");
	}
	runScript(signature);
}

void createRuntimeState(){
	runtimeState = malloc(sizeof(RuntimeState));
	memory = malloc(RuntimeSize);
	runtimeState->freeStart = memory;
	runtimeState->gcThreshold = (UIntP)(0.9 * RuntimeSize);
	runtimeState->memoryLimit = (UIntP)(memory + RuntimeSize);
}

void runScript(char *signature){
	// signature is the signature of a method in the Script class.
}

void createInitialObjects(){
	createSpecialObjects();
	createKernel();
	createExtensions();
}

void createObjectClassMetaclass(){
	
}

void createCharacterTable(){
	createClass
}

void createSpecialObjects(){

Op specialObjects = allocateObject(ArrayFmt,SpecialObjectArraySize,0,0);
runtimeState->firstOp = specialObjects;
Op nullObj = allocateObject(FixedFmt,0, 0, 0);
storeOop(specialObjects,NullSpecialIndex,);
for (int i = 1; i<SpecialObjectArraySize; i++){
	storeOop(specialObjects,i,nullObj);
}

storeOop(specialObjects,FalseSpecialIndex,allocateObject(FixedFmt,0, 0, 0));
storeOop(specialObjects,TrueSpecialIndex,allocateObject(FixedFmt,0, 0, 0));
storeOop(specialObjects,runtimeSpecialIndex,allocateObject(FixedFmt,RuntimeObjSizeInP, 0, nullObj));

storeOop(specialObjects,SmallIntegerSpecialIndex,allocateObject(FixedFmt,ClassSizeInP, 0, nullObj));

#define SmallIntegerSpecialIndex 	(UIntP)5;
#define ArraySpecialIndex 			(UIntP)6;
#define VirtualCallSpecialIndex 	(UIntP)7;

#define NosuchMethodSpecialIndex 	(UIntP)10;
#define UnknownBytecodeSpecialIndex (UIntP)11;
#define MustBeBooleanSpecialIndex 	(UIntP)12;

#define CharacterTableSpecialIndex 	(UIntP)15;
}


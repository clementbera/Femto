#include "types.h"
#include "ObjectAccess.h"
#include "../MemoryManagementCommon"

// This is in header file to be inlined & avoid macro to keep type checks.

/* Header format - single 64 bits word
[GC 8][Fmt 8][size 16][hash 16][cls 16]
GC bits 									up to 8 bits
Fmt (Obj, array, native, immediate, etc.) 	up to 8 bits
size										16 bits 
hash 										16 bits 
classIndex  								16 bits
*/

/* Fmt specification
0 fixed
1 array 
2 weak
 ..
7 immediate
[8-15] Native
*/

#define HeaderSizeInBytes 	8;

UInt16 fetchOpHash(Op op){
	return fetchUInt16(op,-2);
}

UInt16 fetchSmiHash(Smi smi){
	return (UInt16)(smi & 0xFFFF);
}

UInt16 fetchOopHash(Oop oop){
	if (isSmi(oop)){
		return fetchSmiHash((Smi)oop);
	} else {
		return fetchOpHash((Op)oop);
	}
}

void setOpHash(Op op, UInt16 hash){
	storeUInt16(op,-2,hash);
}

UInt16 fetchClassIndex(Op op){
	return fetchUInt16(op,-1));
}

UInt8 fetchFormat(Op op){
	return fetchUInt8(op,-6));
}

UInt16 fetchSizeIn64(Op op){
	return fetchUInt16(op,-3));
}

UIntP fetchNativeSize(Op op, UInt8 format){
	return ((UIntP) fetchSizeIn64(op)) << 3 + (format & 3);
}

UIntP fetchSize(Op op){
	UInt8 fmt = fetchFormat(op);
	if (fmt < 7){
		return (UIntP) fetchSizeIn64(op);
	} else {
		return fetchNativeSize(op, fmt);
	}
}

void setHeader(Op op, UInt16 sizeInP, UInt16 classIndex){
	// 64 bits runtime
	storeUInt64(op, sizeInP << 32 + classIndex)
};

void mark(Op op){
	
}

void unmark(Op op){
	
}

int isMarked(Op op){
	
}
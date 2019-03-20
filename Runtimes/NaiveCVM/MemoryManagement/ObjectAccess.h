#include "types.h"

// This is in header file to be inlined & avoid macro to keep type checks.

char * startOfOp(Op op){
	return (char *) (op - 1);
}

Op opStartingAt(char *start){
	return ((Op) start) + 1;
}

SIntP unboxSmi(Smi smi){
	return (SIntP) smi >> 3;
}

Smi boxSmi(SIntP sIntP){
	return (Smi)((sIntP << 3) & 1);
}

int isSmi(Oop op){
	return op & 1;
}

UInt8 fetchUInt8(Op object, UIntP index){
	return *(UInt8 *)(object + index));
}

void storeUInt8(Op object, UIntP index, UInt8 value){
	*(UInt8 *)(object + index)) = value;
}

UInt16 fetchUInt16(Op object, UIntP index){
	return *(UInt16 *)(object + index));
}

void storeUInt16(Op object, UIntP index, UInt16 value){
	*(UInt16 *)(object + index)) = value;
}

UInt16 fetchUInt32(Op object, UIntP index){
	return *(UInt32 *)(object + index));
}

void storeUInt32(Op object, UIntP index, UInt32 value){
	*(UInt32 *)(object + index)) = value;
}

UInt16 fetchUInt64(Op object, UIntP index){
	return *(UInt64 *)(object + index));
}

void storeUInt64(Op object, UIntP index, UInt64 value){
	*(UInt64 *)(object + index)) = value;
}

Oop fetchOop(Op object, UIntP index){
	return *(Oop *)(object + (index << 3)));
}

void storeOop(Op object, UIntP index, Oop value){
	*(Oop *)(object + (index << 3)) = value;
}


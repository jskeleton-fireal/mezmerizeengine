#pragma once

//this should be included in everything related to merize.
#include "../version.h"
#include "../settings.h"

#ifdef __cplusplus
//assertions for debugging

#include <assert.h>
//stdvector
#include <vector>
//stdstring
#include <string>
//misc functions for stdvectors
#include <algorithm>
//cout
#include <iostream>
//smart pointers
#include <memory>
#else

//memory allocation
#include <malloc.h>

//printf
#include <stdio.h>

//math stuff
#include <math.h>

//assertions for debugging
#include <assert.h>

#endif

//illegal pun cast
#ifndef __cplusplus 
#define reintrp(vValue,vType) (*(vType*)(&vValue))
#define reintrp_p(vValue,vType) (*(vType*)(vValue))
#else
#define reintrp(vValue,vType) (*reinterpret_cast<vType*>(&vValue))
#define reintrp_p(vValue,vType) (*reinterpret_cast<vType*>(vValue))
#define reintrp_noderef(vValue,vType) (reinterpret_cast<vType>(vValue))
#endif


#include "mezvector.h"


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef  char s8;
typedef  short s16;
typedef  int s32;
typedef  long long s64;

typedef u8 bitmask8_t;
typedef u16 bitfield16_t;
typedef u32 bitfield32_t;
typedef u64 bitfield64_t;
typedef u8 cbool_t; //c style bool
typedef void* pointer_t;
typedef void (voidfunction_t)();
typedef int (intfunction_t)();

#ifndef __cplusplus 
typedef cbool_t bool_t; 
enum
{
	false,
	true,
};
#endif

#ifdef __cplusplus 
//dont use using here 
#define stdvector std::vector
#define stdstring std::string
//Im never gonna use these but theyre here
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using std::make_unique;
#endif

//stuff only in debug mode
//use _DEBUG preproccessor for everything else.
#if _DEBUG
#define debugvar(vVar) vVar
#define setdebugvar(vName,vValue) vName = vValue
#else
#define debugvar(vVar) 
#define setdebugvar(vName,vValue) 
#endif




#define possibly_null(v) v

//i cant trust you to just not to use this in c
#ifdef __cplusplus 
#define stdvec_findselection(vVector,vSelection)  std::find(vVector.begin(), vVector.end(), vSelection);
#define stdvec_removeselection(vVector,vSelection) std::erase(vVector,vSelection)
#define inherits : public
#endif

//tricked ya! this doesnt do anything. its there for copy pasting and whatnot 
#define illusionary(v)

//disabled because this sucks and i dont know what i was thinking
#if 0
//for when pragma once decides to be a little lame. THIS IS TERRIBLE!!!!
#define trustmeptr(vTypeName) void*
//use with trustmeptr
#define itrustyou(vVariable,vTypename) vTypename* tru##vVariable = reintrp(vVariable,vTypename*)
#else
#define trustmeptr(vTypeName) vTypeName*
#define itrustyou(vVariable,vTypename) vTypename* tru##vVariable = reintrp(vVariable,vTypename*)
#endif

//this is terrible LOL
#define assert_msg(vCheckval,vMessage) assert(vCheckval illusionary(vMessage));

#define function_body_not_implemented assert_msg(0,"function_body_not_implemented")




#define INHERIT_CONSTRUCTOR(vClassname) using vClassname::vClassname;

#ifdef __cplusplus
//hehehe
//This is illegal btw
template <typename TYPE,typename TYPE2>
TYPE remove_const(const TYPE2 thing)
{
	pointer_t test = (pointer_t) & thing;
	return reintrp_noderef(test,TYPE);
}
#endif
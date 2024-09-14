#pragma once
#include <cstdarg>
#include <stdio.h>

//a very small class for static formatting... Do not use this in place of mezstrings

#define buffer_size 500
struct MezString;
class static_format_t
{
public:
	char buffer[buffer_size];
	operator char*() { return buffer; }
	operator MezString();
	
};
static_format_t static_format(const char* format, ...);

#pragma once
#include <cstdarg>
#include <stdio.h>

#define buffer_size 500
class static_format_t
{
public:
	char buffer[buffer_size];
	operator char*() { return buffer; }
	
};
static_format_t static_format(const char* format, ...);

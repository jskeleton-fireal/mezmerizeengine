#include "static_format.h"
#include "mezstring.h"

void nonstatic_format(char* buffer, const char* format, ...);

static_format_t static_format(const char* format, ...)
{
	static_format_t c;
	nonstatic_format(c.buffer, format);
	return c;
}

void nonstatic_format(char* buffer, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int v = vsnprintf(buffer, buffer_size, format, args);
	//if (v) perror(buffer);
	va_end(args);
	return;
}

static_format_t::operator MezString()
{
	return MezString(buffer);
}

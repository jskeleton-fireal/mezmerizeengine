#pragma once
#include "../merize.h"
#include "cvhandler.h"
enum
{
	CONTHING_FLAG_DEVELOPMENT = (1 << 0),
	CONTHING_FLAG_HIDDEN = (1 << 1),
};

//what factories use internally
class ConsoleThing
{
public:
	const char* m_Name;
	bitfield16_t m_Flags; //This can be promoted to bitfield32_t
	int m_engine; //if SUPPORT_MULTIPLE_ENGINES is 0, this is unused padding
public:
	virtual possibly_null(pointer_t) Execute(const char* f_i) = 0;

public:
	ConsoleThing(const char* f_name, bitfield16_t f_flags = 0);
	virtual const char* ct_type_name() { return "undef"; }
	bool is_global_reference();
	virtual bool is_oneshot() { return false; }
protected:
	void Upload();
	int get_engine_id();
};

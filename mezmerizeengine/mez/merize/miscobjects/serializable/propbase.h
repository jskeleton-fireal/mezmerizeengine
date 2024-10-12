#pragma once
#include <mez/merize/merize.h>


//base class for properties and whatnot.
//this gets serialized!


class PropBase
{
public:
	const char* m_name;
	bitfield16_t m_flags;

	//returns the VALUE OF THE OBJECT as a string
	virtual mezstring_t ToString() { return ""; }
};
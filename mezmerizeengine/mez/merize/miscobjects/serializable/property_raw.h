#pragma once

#include "datatype.h"
#include "../../merize.h"
#include "../../helpers/mezstring.h"

class RawProperty
{
	friend class MezSerializable; //Does not respect inheritence, which is good!
public:
	void* m_location;
	u16 m_size;
	bitfield16_t m_flags;
	datatype_t m_datatype;
	const char* m_name;

	RawProperty() {}
	RawProperty(void* f_location, int f_size, datatype_t f_datatype,const char* f_name);
	RawProperty(void* f_location, int f_size, bitfield16_t f_flags,datatype_t f_datatype,const char* f_name);

	mezstring_t ToString();
	void FromString(const char* f_text);
protected: 	//for serializer only.
	//THIS SETS DATA IN m_location!!!
	//expects m_datatype to be set.
	void FromString_OldReallybadSucksREMOVETHISPLEASE(const char* f_text, int* errorcode_pointer,char strend_char = ';');
};
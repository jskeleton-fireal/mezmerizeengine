#pragma once

#include "datatype.h"
#include "../../merize.h"
#include "../../helpers/mezstring.h"

#include "propbase.h"

class RawProperty : public PropBase
{
	friend class MezSerializable; //Does not respect inheritence, which is good!
public:
	void* m_location;
	u16 m_size;
	datatype_t m_datatype;

	RawProperty() {}
	RawProperty(void* f_location, int f_size, datatype_t f_datatype,const char* f_name);
	RawProperty(void* f_location, int f_size, bitfield16_t f_flags,datatype_t f_datatype,const char* f_name);

	virtual mezstring_t ToString();
	void FromString(const char* f_text);
protected: 	//for serializer only.
	//THIS SETS DATA IN m_location!!!
	//expects m_datatype to be set.
	void FromString_OldReallybadSucksREMOVETHISPLEASE(const char* f_text, int* errorcode_pointer,char strend_char = ';');
};
#pragma once
#include "format.h"


class MezSFormat_Mez : public MezSFormat_Base
{
public:


	virtual mezstring_t ToLine(PropBase* f_property);

	virtual void OnSerializeStart(mezstring_t* final_string);

	virtual bool Deserialize(const char* f_text, PropertiesVector* f_target);
	virtual bool Deserialize_Line(const char* f_text, PropertiesVector* f_target);
};
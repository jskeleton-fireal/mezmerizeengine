#pragma once

#include "property_raw.h"
#include "../../helpers/mezstring.h"
#include <vector>
#include "prop_container.h"
#include "../propobject/propobject.h"


//typedef stdvector<PropBase> PropertiesVector;
#define PropertiesVector PropertyContainer
//generic class for serialziing.
//Uses properties.
static class MezSerialize
{
public:
	//supported formats:
	//MezSerializeFormat - mezmerize serialize format. its gud trust

	//these need to be versioned like this for backwards compatibility
	enum SerializeFormat
	{
		SFMT_MezSerializeFormat_V1,

		SFMT_MezSerializeFormat = SFMT_MezSerializeFormat_V1,

		SFMT_Default = SFMT_MezSerializeFormat,
	};

public:
	static mezstring_t Serialize(MezPropertyObject* f_object,SerializeFormat f_format = SFMT_Default);
	static bool DeSerialize(MezPropertyObject* f_object,const char* f_string,SerializeFormat f_format = SFMT_Default);
	static 
	bool SerializeToFile(MezPropertyObject* f_object,const char* f_file,SerializeFormat f_format = SFMT_Default);
};
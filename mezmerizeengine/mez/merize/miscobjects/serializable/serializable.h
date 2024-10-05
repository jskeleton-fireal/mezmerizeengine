#pragma once

#include "property_raw.h"
#include "../../helpers/mezstring.h"
#include <vector>

typedef stdvector<RawProperty> PropertiesVector;
//generic class for serialziing.
//Uses properties.
class MezSerializable
{
public:
	//supported formats:
	//MezSerializeFormat - custom format for serializing. great for debugging and other purposes
	//Json - because im nice :)

	//these need to be versioned like this for backwards compatibility
	enum SerializeFormat
	{
		SFMT_MezSerializeFormat_V1,
		SFMT_Json_V1,


		//use these :)
		SFMT_MezSerializeFormat = SFMT_MezSerializeFormat_V1,
		SFMT_Json = SFMT_Json_V1,

		SFMT_Default = SFMT_MezSerializeFormat,
		SFMT_AutoDetermine = -1,
	};

public:
	PropertiesVector GetProperties();
	virtual mezstring_t Serialize(SerializeFormat f_format = SFMT_Default);
	virtual bool DeSerialize(const char* f_string,SerializeFormat f_format = SFMT_AutoDetermine);
protected:
	virtual void DeclareProperties(PropertiesVector* vector) { }
};
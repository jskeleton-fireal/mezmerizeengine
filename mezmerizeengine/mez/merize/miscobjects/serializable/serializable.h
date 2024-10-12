#pragma once

#include "property_raw.h"
#include "../../helpers/mezstring.h"
#include <vector>
#include "prop_container.h"


//typedef stdvector<PropBase> PropertiesVector;
#define PropertiesVector PropertyContainer
//generic class for serialziing.
//Uses properties.
class MezSerializable
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
	PropertiesVector GetProperties();
	virtual mezstring_t Serialize(SerializeFormat f_format = SFMT_Default);
	virtual bool DeSerialize(const char* f_string,SerializeFormat f_format = SFMT_Default);
	bool SerializeToFile(const char* f_file,SerializeFormat f_format = SFMT_Default);
protected:
	virtual void DeclareProperties(PropertiesVector* vector) { }
public:
	virtual const char* GetClassname() { return 0; }
};
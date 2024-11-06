#include "serialize.h"
#include "../../helpers/static_format.h"
#include "format/format.h"
#include "format/format_mez.h"
#include <fstream>

//todo: move formats into their own classes? im not sure how exactly that would work.. but it would be so so nice


shared_ptr<MezSFormat_Base> make_formatter(MezSerialize::SerializeFormat format)
{
	switch (format)
	{
	case MezSerialize::SFMT_MezSerializeFormat_V1:
		return std::make_shared<MezSFormat_Mez>();
	}
	return 0;
}


char getsep(MezSerialize::SerializeFormat format)
{
	switch (format)
	{
	case MezSerialize::SerializeFormat::SFMT_MezSerializeFormat_V1:
		return '>';
	}
	return ';';
}


mezstring_t MezSerialize::Serialize(MezPropertyObject* f_object,SerializeFormat f_format)
{
	PropertiesVector props = f_object->GetProperties();
	shared_ptr<MezSFormat_Base> formatter = make_formatter(f_format);

	mezstring_t finalone = "";
	formatter.get()->m_prop_count = props.size();
	formatter.get()->OnSerializeStart(&finalone);
	for (int i = 0; i < props.size(); i++)
	{
		formatter.get()->m_prop_number = i;
		mezstring_t string = formatter.get()->ToLine(props[i]);
		finalone.append(string);
	}
	formatter.get()->OnSerializeEnd(&finalone);
    return finalone;
}

bool MezSerialize::DeSerialize(MezPropertyObject* f_object, const char* f_string, SerializeFormat f_format)
{
	f_format = SFMT_Default; //testing
	PropertiesVector props = f_object->GetProperties();
	shared_ptr<MezSFormat_Base> formatter = make_formatter(f_format);
	return formatter.get()->Deserialize(f_string,&props);
}

bool MezSerialize::SerializeToFile(MezPropertyObject* f_object, const char* f_file, SerializeFormat f_format)
{
	mezstring_t str = Serialize(f_object);
	if (!str.length()) return false;
	std::fstream output;
	output.open(f_file,std::ios::out);
	if (output.bad()) return false;
	output.write(str.cstr_const(), str.length());
	output.close();
	return true;
}

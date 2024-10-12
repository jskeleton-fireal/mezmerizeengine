#include "serializable.h"
#include "../../helpers/static_format.h"
#include "format/format.h"
#include "format/format_mez.h"
#include <fstream>

//todo: move formats into their own classes? im not sure how exactly that would work.. but it would be so so nice


shared_ptr<MezSFormat_Base> make_formatter(MezSerializable::SerializeFormat format)
{
	switch (format)
	{
	case MezSerializable::SFMT_MezSerializeFormat_V1:
		return std::make_shared<MezSFormat_Mez>();
	}
	return 0;
}

PropertiesVector MezSerializable::GetProperties()
{
	PropertiesVector props;
	DeclareProperties(&props);
	return props;
}
char getsep(MezSerializable::SerializeFormat format)
{
	switch (format)
	{
	case MezSerializable::SerializeFormat::SFMT_MezSerializeFormat_V1:
		return '>';
	}
	return ';';
}


mezstring_t MezSerializable::Serialize(SerializeFormat f_format)
{
	PropertiesVector props = GetProperties();
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

bool MezSerializable::DeSerialize(const char* f_string, SerializeFormat f_format)
{
	f_format = SFMT_Default; //testing
	PropertiesVector props = GetProperties();
	shared_ptr<MezSFormat_Base> formatter = make_formatter(f_format);
	return formatter.get()->Deserialize(f_string,&props);
}

bool MezSerializable::SerializeToFile(const char* f_file, SerializeFormat f_format)
{
	mezstring_t str = Serialize();
	if (!str.length()) return false;
	std::fstream output;
	output.open(f_file,std::ios::out);
	if (output.bad()) return false;
	output.write(str.cstr_const(), str.length());
	output.close();
	return true;
}

#include "property_raw.h"
#include "../../helpers/mezstring.h"

RawProperty::RawProperty(void* f_location, int f_size, datatype_t f_datatype, const char* f_name)
{
	m_location = f_location;
	m_size = f_size;
	m_datatype = f_datatype;
	m_name = f_name;
}

RawProperty::RawProperty(void* f_location, int f_size, bitfield16_t f_flags, datatype_t f_datatype, const char* f_name)
{
	m_location = f_location;
	m_size = f_size;
	m_datatype = f_datatype;
	m_name = f_name;
	m_flags = f_flags;
}

#define itoa _itoa_s

mezstring_t RawProperty::ToString()
{
#define locfunc(vType,vFunc) vFunc(*((vType*)m_location), buffer, 128)
	char buffer[128];
	buffer[0] = '\0';
	switch (m_datatype)
	{
	case (DataType::DT_Int32): locfunc(int, itoa); break;
		//todo: check to see how many decimal places we need
	case (DataType::DT_Float): sprintf_s(buffer, "%.2f",(*(float*)m_location)); break;
	case (DataType::DT_String): memcpy(m_location, buffer,fmin(127,strlen((const char*)m_location))); break;
	case (DataType::DT_Boolean): sprintf_s(buffer, "%s",(!(*(bool*)m_location)) ? "true" : "false"); break;
	default: 
		assert_msg(0,"datatype has no converter?");
	case (DataType::DT_Byte):
		locfunc(u8, itoa); break;
	case (DataType::DT_SignedByte):
		locfunc(s8, itoa); break;
	}

	//copy buffer, and package
	return mezstring_t(buffer);
}

void RawProperty::FromString(const char* f_text)
{
	if (!f_text || !f_text[0]) return;
	switch (m_datatype)
	{
	case DataType::DT_Boolean:
	{
		//supports True and true, but doesnt support 1 and 0.
		//This is OKAY for 1 and 0. char at index 1 will be the terminator!

		//Using u8 instead of bool cause c++ is weird with bools and i dont want it using any unnecessary optimizations
		*(u8*)m_location = f_text[1] == 'r';
		break;
	}
	case DataType::DT_Float:
	{
		*(float*)m_location = atof(f_text);
		break;
	}
	case DataType::DT_Byte:
	{
		*(u8*)m_location = atoi(f_text) % 0x100;
		break;
	}
	case DataType::DT_SignedByte:
	{
		*(s8*)m_location = atoi(f_text) % 0x100;
		break;
	}
	case DataType::DT_Int32:
	{
		*(int*)m_location = atoi(f_text);
		break;
	}

	default:
		assert(0);
		break;
	}

}

void RawProperty::FromString_OldReallybadSucksREMOVETHISPLEASE(const char* f_text, int* errorcode_pointer,char strend_char)
{
#define set_errorcode(vVal) if(errorcode_pointer) *errorcode_pointer = vVal
	//dont feed a bad string into this please
	if (!f_text[0]) set_errorcode(1); return;

	int ending = -1;
	while (ending++)
	{
		if (f_text[ending] == strend_char)
		{
			break;
		}
	}

	//hell yeah.
	//dw we set this back at the end.
	//THIS IS NEEDED FOR basic c stuff like atoi to work. cause it thinkts its the end
	char* noconst = remove_const<char*>(f_text);
	noconst[ending] = '\0';

	//DO NOT HAVE A RETURN IN HERE!!
	switch (m_datatype)
	{
	case DataType::DT_Boolean:
		{
		//supports True and true, but doesnt support 1 and 0.
		//This is OKAY for 1 and 0. char at index 1 will be the terminator!
		
		//Using u8 instead of bool cause c++ is weird with bools and i dont want it using any unnecessary optimizations
		*(u8*)m_location = f_text[1] == 'r';
		set_errorcode(0);
		break;
		}
	case DataType::DT_Float:
		{
		*(float*)m_location = atof(f_text);
		set_errorcode(0);
		break;
		}
	case DataType::DT_Byte:
		{
		*(u8*)m_location = atoi(f_text) % 0x100;
		set_errorcode(0);
		break;
		}	
	case DataType::DT_SignedByte:
		{
		*(s8*)m_location = atoi(f_text) % 0x100;
		set_errorcode(0);
		break;
		}
	case DataType::DT_Int32:
	{
		*(int*)m_location = atoi(f_text);
		set_errorcode(0);
		break;
	}

	default:
		assert(0);
		break;
	}

	noconst[ending] = strend_char;
}

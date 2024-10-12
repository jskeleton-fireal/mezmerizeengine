#pragma once


struct DataType
{
public:
	int m_data_type;
public:
	enum
	{
		DT_Int32 = 0x1,
		DT_Float = 0x2,
		DT_Boolean = 0x5,
		DT_Byte = 0x81,
		DT_SignedByte = 0x1081,
		//handled differently
		DT_String = 0x10000,
	};

	typedef int bitcount_t;
	bitcount_t GetDataSize();
	bitcount_t GetMinimumDataSize();
	const char* ToString();

	operator int() { return m_data_type; }

	DataType() { }
	DataType(const int& i) { m_data_type = i; }

};

typedef struct DataType datatype_t;
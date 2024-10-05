#include "datatype.h"
#include "../../helpers/mezstring.h"

int DataType::GetDataSize()
{
    switch (m_data_type)
    {
    case DT_Int32:
    case DT_Float:
        return 32;
    case DT_Byte:
    case DT_Boolean:
        return 8;
    }
    return 64; //just include all of it
}

int DataType::GetMinimumDataSize()
{
    switch (m_data_type)
    {
    case DT_Boolean: //bools only need one bit
        return 1;
    }
    return GetDataSize();
}

//NEVER change these.
const char* DataType::ToString()
{
    switch (m_data_type)
    {
    case DT_Boolean: return "bool";
    case DT_Byte: return "byte";
    case DT_SignedByte: return "sbyte";
    case DT_Int32: return "int";
    case DT_Float: return "float";
    case DT_String: return "string";
    }
    return "unknown";
}

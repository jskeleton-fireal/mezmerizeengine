#include "format_mez.h"
#include "../../../helpers/static_format.h"
mezstring_t MezSFormat_Mez::ToLine(RawProperty f_property)
{

    mezstring_t prop = f_property.ToString();

    char buffer[500];
    sprintf_s(buffer, "[%s::%s => %s]\n", f_property.m_name, f_property.m_datatype.ToString(), prop.cstr_const());
    m_current_line++;
    return mezstring_t(buffer);
}

void MezSFormat_Mez::OnSerializeStart(mezstring_t* final_string)
{
    final_string->append("#mezserialize_v1\n");
    m_current_line++;
}

bool MezSFormat_Mez::Deserialize(const char* f_text, PropertiesVector* f_target)
{
    int lines = count_lines(f_text);
    bool vval = true;
    for (int i = 1; i < lines; i++)
    {
        mezstring_t line = get_line(f_text, i);
        vval &= Deserialize_Line(line, f_target);
    }
    return vval;
}

bool has_within(const char* txt1, const char* txt2, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (txt1[i] != txt2[i]) return false;
    }
    return true;
}

bool MezSFormat_Mez::Deserialize_Line(const char* f_text, PropertiesVector* f_target)
{
    mezstring_t meztext = f_text;
    mezstring_t property_name = meztext.substring_until(1, ':');
    bool is_good = false;
    RawProperty* prop = 0;
    for (int i = 0; i < f_target->size(); i++)
    {
        if (!strcmp(f_target->at(i).m_name, property_name))
        {
            //this is the property

            is_good = true;
            prop = &f_target->at(i);
            break;
        }
    }
    
    if (!is_good) return false;

    
    for (int i = 0; i < meztext.length(); i++)
    {
        if (f_text[i] == '>')
        {
            prop->FromString(meztext.substring_until(i + 1, ']'));
            return true;
        }
    }

    return false; //shouldnt get here
}

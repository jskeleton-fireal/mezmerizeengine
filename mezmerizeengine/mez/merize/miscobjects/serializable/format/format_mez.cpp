#include "format_mez.h"
#include "../../../helpers/static_format.h"
#include <mez/merize/console/cmd.h>

constexpr char padding_char = ' ';

mezstring_t MezSFormat_Mez::ToLine(PropBase* f_property)
{
    const int buffa_size = 500;
    char buffer_true[500];
    memset(buffer_true, padding_char, m_section_index);
    char* buffer = (buffer_true) + m_section_index;
    int final_size = buffa_size - m_section_index;
    if (RawProperty* rawproperty = dynamic_cast<RawProperty*>(f_property))
    {
        mezstring_t prop = rawproperty->ToString();

        sprintf_s(buffer, final_size, "[%s => %s]\n", rawproperty->m_name, prop.cstr_const());
        m_current_line++;
        return mezstring_t(buffer_true);
    }
    if (RawPropSection* section = dynamic_cast<RawPropSection*>(f_property))
    {

        if (!section->m_end)
        {
            m_section_index++;
            sprintf_s(buffer, final_size, "%s: {\n", section->m_name);
        }
        else
        {
            m_section_index--;
            sprintf_s(buffer, final_size, "}\n");
        }
        m_current_line++;
        return mezstring_t(buffer_true);
    }
}

void MezSFormat_Mez::OnSerializeStart(mezstring_t* final_string)
{
    final_string->append("#v1\n");
    m_current_line++;
}

bool MezSFormat_Mez::Deserialize(const char* f_text, PropertiesVector* f_target)
{
    int lines = count_lines(f_text);
    bool vval = true;
    for (int i = 1; i < lines; i++)
    {
        mezstring_t line = get_line(f_text, i);
        bool success = Deserialize_Line(line, f_target);
        vval &= success;
        if (!success)
        {
#if _DEBUG
            console_printf("failed to deserialize\n");
#endif
            return 0;
        }

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

//sux
bool MezSFormat_Mez::Deserialize_Line(const char* f_text, PropertiesVector* f_target)
{
    mezstring_t meztext = f_text;
    bool is_section_declaration = false;
    for (int i = 0; i < 999; i++)
    {
        if (f_text[i] == '}')
        {
            //broke out of section
            m_section_index--;
            if (m_section_index < 0) return false;
            m_section_depth.pop_back();
            return true;
        }        
        if (f_text[i] == '{')
        {
            //section declaration
            is_section_declaration = true;
            break;
        }
        if (f_text[i] == 0) break;
    }

    //need to ignore tabs
    for (int i = 0; i < 999; i++)
    {
        if (f_text[i] != padding_char) { meztext = meztext.substring(i); break; }
        if (f_text[i] == 0) return false;
    }

    mezstring_t property_name;
    if (is_section_declaration)
    {
        property_name = meztext.substring_until(0, ':');
    }
    else
    {
        property_name = meztext.substring_until(1, ' ');
    }
    bool is_good = false;
    RawProperty* prop = 0;
    for (int i = 0; i < f_target->size(); i++)
    {
        const char* itname = f_target->at(i)->m_name;
        if (itname&&!strcmp(itname, property_name))
        {
            if (is_section_declaration)
            {
                m_section_index++;
                m_section_depth.push_back(dynamic_cast<RawPropSection*>(f_target->at(i)));
                return true;
            }
            //this is the property
            prop = dynamic_cast<RawProperty*>(f_target->at(i));
            is_good = prop;
            if (is_good)
            break;
        }
    }
    
    if (!is_good) return false;

    
    for (int i = 0; i < meztext.length(); i++)
    {
        if (f_text[i] == '>')
        {
            mezstring_t val = meztext.substring_until(i, ']');
            if (!val.length()) return false;
            prop->FromString(val);
            return true;
        }
    }

    return false; //shouldnt get here
}

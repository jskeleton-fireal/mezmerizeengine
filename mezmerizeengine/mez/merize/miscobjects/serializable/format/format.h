#pragma once
#include "../../../helpers/mezstring.h"
#include "../property_raw.h"
#include "../property_section.h"
#include "../serializable.h"


class MezSFormat_Base
{
public:
	int m_prop_number;
	int m_prop_count;
protected:
	int m_current_line = 0;
	int m_section_index = 0;
	std::vector<RawPropSection*> m_section_depth;
public:
	virtual void OnSerializeStart(mezstring_t* final_string) {}
	virtual mezstring_t ToLine(PropBase* f_property) = 0;
	virtual void OnSerializeEnd(mezstring_t* final_string) {}

	virtual bool Deserialize(const char* f_text,PropertiesVector* f_target) = 0;
	virtual bool Deserialize_Line(const char* f_text, PropertiesVector* f_target) = 0;

	bool is_last_line() { return m_prop_number == m_prop_count-1; }
	int count_characters(const char* text,char character)
	{
		int ic = 0;
		int i = 0;
		while (i+1)
		{
			if (!text[i]) break;
			if (text[i] == character) ic++;
			i++;
		}
		return ic;
	}

	int count_lines(const char* text) { return count_characters(text,'\n'); }

	mezstring_t get_line(const char* text, int line,char nl='\n')
	{
		int line_2 = line + 1;
		int instances = 0;
		int i = 0;
		int last = 0;
		while (true)
		{
			if (text[i] == nl)
			{
				instances++;
				if (instances == line_2)
				{
					int size = i - last;
					char it[300];
					memcpy(it, text + last+1, size);
					it[size] = '\0';
					return it;
				}
				last = i;
			}
			i++;
		}
	}
};
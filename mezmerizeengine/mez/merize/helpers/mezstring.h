#pragma once
#include "../merize.h"

struct MezString
{
private:
	union { const char* m_const; char* m_; } m_buffer;

public:
	char* cstr();
	const char* cstr_const();
	void set_cstr(const char* cstr);
	void append(const char* cstr);
	MezString substring(int start);
	MezString substring(int start,int end);
	MezString substring_until(const char until_this_char);
	MezString substring_until(int start,const char until_this_char);
	int length();
	inline void clone(MezString* other)
	{
		m_buffer.m_ = other->m_buffer.m_;
		newbuffer();
	}
	bool valid() { return m_buffer.m_; }
private:
	void newbuffer(int size = -1,bool copy_previous = true,bool deallocate_previous = false);
public:
	operator char* () { return cstr(); }
	operator const char* () { return cstr_const(); }
	MezString operator=(const char* cstring) { return MezString(cstring); }
	//MezString& operator=(const MezString& other); 
	void free();
	MezString(); 
	MezString(const MezString& copy);
	MezString(const char* c_str);
	~MezString();
	void debug_logself(bool selfisvalid=true);
};

typedef struct MezString mezstring_t;
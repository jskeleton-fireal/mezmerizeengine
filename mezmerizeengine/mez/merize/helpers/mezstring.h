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
#if 0
	inline MezString clone()
	{
		MezString nustr = MezString();
		nustr.m_buffer.m_ = m_buffer.m_;
		nustr.newbuffer();
		return nustr;
	}
#else
	inline void clone(MezString* other)
	{
		m_buffer.m_ = other->m_buffer.m_;
		newbuffer();
	}
#endif
	bool valid() { return m_buffer.m_; }
private:
	void newbuffer(int size = -1,bool copy_previous = true,bool deallocate_previous = false);
public:
	operator char* () { return cstr(); }
	operator const char* () { return cstr_const(); }
	//MezString& operator=(const MezString& other); 
	void free();
	MezString(); 
	MezString(const MezString& copy);
	MezString(const char* c_str);
	~MezString();
	void debug_logself(bool selfisvalid=true);
};

typedef struct MezString mezstring_t;
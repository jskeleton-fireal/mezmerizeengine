#pragma once
#include "../merize.h"

//this is for later.....
enum CVHANDLER_TYPE
{
	CVHANDLER_TYPE_UNKNOWN,
	CVHANDLER_TYPE_INT = 0x40,
	CVHANDLER_TYPE_STRING = 0x80,
	CVHANDLER_TYPE_BOOL = 0x10,
	CVHANDLER_TYPE_FLOAT = 0x4f,
};

union cv_typeclump
{
	float m_float;
	int m_int;
	bool m_bool;
	s64 m_long;
};

typedef union cv_typeclump cv_typeclump_t;

//dont use a template here. we dont want ugly dynamic casts every time a consolevariable is accessed. this is good enough
class CVHandler {
public:
	virtual CVHANDLER_TYPE GetType() = 0;
	virtual int GetInt() { return -1; }
	virtual const char* GetString() { return 0; }
	virtual bool GetBool() { return !!GetInt(); }
	virtual float GetFloat() { return -1.0f; }
	virtual pointer_t GetValPtr() { return Execute(); }
	virtual cv_typeclump_t GetClumped()
	{
		return reintrp_p(GetValPtr(),cv_typeclump_t);
	}
public:
	virtual pointer_t Execute() = 0; //make this a pointer to whatever variable y oure using
	virtual int GetSize() = 0; //You need to set this
	//Only call this internally. DO NOT SEND USER INPUT TO THIS FUNCTION EVER.
	virtual void Set_Internal(pointer_t ptrtoval)
	{
		memcpy_s(Execute(), GetSize(), ptrtoval, GetSize());
	}

	virtual bool ParseFromString(const char* m_str) = 0;
	virtual const char* GetDisplayString() = 0; //Pretty name
};



class CVHandler_int : public CVHandler
{
public:
	typedef int dsg_type_t;
private:
	dsg_type_t m_val;
public:
	virtual pointer_t Execute() { return &m_val; }
	virtual CVHANDLER_TYPE GetType() { return CVHANDLER_TYPE_INT; }
	virtual int GetInt() { return m_val; }
	virtual int GetSize() { return sizeof(int); }
	void Set(dsg_type_t f_val) { m_val = f_val; }

	virtual bool ParseFromString(const char* m_str) { m_val = atoi(m_str); return true; }
	virtual const char* GetDisplayString() { char buff[255]; sprintf_s(buff,"%i",m_val); return buff; }
};

class CVHandler_float : public CVHandler
{
public:
	typedef float dsg_type_t;
private:
	float m_val;
public:
	virtual pointer_t Execute() { return &m_val; }
	virtual CVHANDLER_TYPE GetType() { return CVHANDLER_TYPE_FLOAT; }
	virtual float GetFloat() { return m_val; }
	virtual int GetSize() { return sizeof(float); }
	void Set(dsg_type_t f_val) { m_val = f_val; }
	virtual bool ParseFromString(const char* m_str) { m_val = atof(m_str); return true; }
	virtual const char* GetDisplayString() { char buff[255]; sprintf_s(buff, "%.4f", m_val); return buff; }
};

class CVHandler_bool : public CVHandler
{
public:
	typedef bool dsg_type_t;
private:
	bool m_val;
public:
	virtual pointer_t Execute() { return &m_val; }
	virtual CVHANDLER_TYPE GetType() { return CVHANDLER_TYPE_BOOL; }
	virtual int GetInt() { return m_val; }
	virtual bool GetBool() { return m_val; }
	virtual int GetSize() { return sizeof(bool); }
	void Set(dsg_type_t f_val) { m_val = f_val; }
	virtual bool ParseFromString(const char* m_str) { m_val = atoi(m_str); return true; }
	virtual const char* GetDisplayString() { char buff[255]; sprintf_s(buff, "%i", m_val); return buff; }
};

//C style strings. not sure how c++ stdstrings will work with this system
class CVHandler_string_c : public CVHandler
{
public:
	typedef const char* dsg_type_t;
private:
	const char* m_val;
public:
	virtual pointer_t Execute() { return &m_val; }
	virtual CVHANDLER_TYPE GetType() { return CVHANDLER_TYPE_STRING; }
	virtual const char* GetString() { return m_val; }
	virtual int GetSize() { return sizeof(const char*); }
	void Set(dsg_type_t f_val) { m_val = f_val; }
};

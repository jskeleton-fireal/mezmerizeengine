#pragma once
#include "conthing.h"
#include "cvhandler.h"
#include "../staticdefs.h"
#include "cmdargs.h"
//Temporary
#define console_printf printf
//#define console_printf 


enum ConsoleCommandResult
{
	CONCMDRES_FINISHED,
	CONCMDRES_FAILED,
	CONCMDRES_BADARGS,
};

typedef int (concmd_functype_raw_t)(ConCommandArgs*);
typedef concmd_functype_raw_t* concmd_functype_t;

class ConsoleCommand : public ConsoleThing
{
public:
	concmd_functype_t m_func;
	virtual possibly_null(pointer_t) Execute(const char* f_i)
	{
		ConCommandArgs args = ConCommandArgs(f_i);
		return (pointer_t)m_func(&args);
	}

	ConsoleCommand(const char* f_name, bitfield16_t f_flags, concmd_functype_t f_func) : ConsoleThing(f_name,f_flags)
	{
		m_func = f_func;
	}
	virtual const char* ct_type_name() { return "cmd"; }
	virtual bool is_oneshot() { return true; }

	virtual bool console_execute(class ConCommandArgs args, const char* input);
};
template <typename CVType = int>
class CV_Constraint
{
public:
	bool m_enabled;
	CVType m_min;
	CVType m_max;
};

//DO NOT CREATE INSTANCES OF THIS. this is just a generic type to dynamic cast consolethings to
class ConsoleVariable_Generic : public ConsoleThing
{
private:
public:
	virtual possibly_null(pointer_t) Execute( const char* f_i) { return this; }
	ConsoleVariable_Generic(const char* f_name, bitfield16_t f_flags) : ConsoleThing(f_name, f_flags)
	{

	}
public:
	virtual const char* ct_type_name() { return "var??"; }

	virtual int GetInt() = 0;
	virtual float GetFloat() = 0;
	virtual const char* GetString() = 0;
	virtual bool GetBool() = 0;

	virtual bool console_execute(class ConCommandArgs args, const char* input);
	virtual CVHandler* GetHandler() = 0;

	explicit operator int() { return GetInt(); }
	explicit operator float() { return GetFloat(); }
	explicit operator const char* () { return GetString(); }
	explicit operator bool() { return GetBool(); }
};


//RootType must match CVHandlerType
template <class CVHandlerType,typename RootType>
class ConsoleVariable_Typed : public ConsoleVariable_Generic
{
private:
	CVHandlerType* m_handler;
public:
	virtual possibly_null(pointer_t) Execute(const char* f_i) { return this; }
	ConsoleVariable_Typed(const char* f_name, bitfield16_t f_flags, RootType f_default_value, CV_Constraint<RootType> f_constraint = {0,0,0}) : ConsoleVariable_Generic(f_name, f_flags)
	{
		m_handler = new CVHandlerType();
		m_handler->Set(f_default_value);
		m_constraint = f_constraint;
	}

	~ConsoleVariable_Typed()
	{
		delete m_handler;
	}
public:
	CV_Constraint<RootType> m_constraint;

	virtual const char* ct_type_name() { return static_format("val.%02x",m_handler->GetType()); }

	virtual int GetInt() { return m_handler->GetInt(); }
	virtual float GetFloat() { return m_handler->GetFloat(); }
	virtual const char* GetString() { return m_handler->GetString(); }
	virtual bool GetBool() { return m_handler->GetBool(); }

	virtual CVHandler* GetHandler() { return m_handler; }
};

#define QUIKMAC_MAKETYPEDCONVAR(vName,vHandler,vType,VType2) class vName : public ConsoleVariable_Typed<vHandler, vType> {  public: using ConsoleVariable_Typed::ConsoleVariable_Typed; operator vType() { return Get##VType2##(); }};

//these used to be just typedefs but i want implicit operators so you can quickly swap from a local variable to a convar in the same file

QUIKMAC_MAKETYPEDCONVAR(ConsoleVariableBool, CVHandler_bool, bool, Bool);
QUIKMAC_MAKETYPEDCONVAR(ConsoleVariableInt, CVHandler_int, int, Int);
QUIKMAC_MAKETYPEDCONVAR(ConsoleVariableFloat, CVHandler_float, float, Float);
QUIKMAC_MAKETYPEDCONVAR(ConsoleVariableStringC, CVHandler_string_c, const char*, String);




extern ConsoleVariableBool cv_developer;

//not supported anymore
#if 0
#define CREATE_CONSOLEVARIABLE(vName,vType,vFlags,vDefaultValue) ConsoleVariable_Typed<CVHandler_##vType,vType> cv_##vName = ConsoleVariable_Typed<CVHandler_##vType,vType>(#vName, vFlags, vDefaultValue, {0,0,0}) 
#define CREATE_CONSOLEVARIABLE_CONSTRAINED(vName,vType,vFlags,vDefaultValue,vMin,vMax) ConsoleVariable_Typed<CVHandler_##vType,vType> cv_##vName = ConsoleVariable_Typed<CVHandler_##vType,vType>(#vName, vFlags, vDefaultValue, {1,vMin,vMax}) 
#define CREATE_CONSOLEVARIABLE_BOOL(vName,vFlags,vDefaultValue) CREATE_CONSOLEVARIABLE_CONSTRAINED(vName,bool,vFlags,vDefaultValue,0,1)
#endif
//i KNOW youre gonna see this and forget everything abt this so HERES SOME BASIC DOCS.
// args are (cmdname,flags) cmdname IS NOT A STRING. return 0 if everything went well
#define CREATE_CONSOLECOMMAND_WFUNC(vName,vFlags) int __cmdfunc__##vName(ConCommandArgs* f_args);  ConsoleCommand __cmd__##vName = ConsoleCommand(#vName,vFlags,__cmdfunc__##vName); int __cmdfunc__##vName(ConCommandArgs* f_args)


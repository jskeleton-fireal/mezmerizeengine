#pragma once


class ConCommandArgs_Single
{
	friend class ConCommandArgs;
private:
	const char* m_spot;
public:
	ConCommandArgs_Single(const char* f_spot);
	bool Valid();
	//Do not call this function if not valid. Ever.
	int Length();

	void GetString(char* buffer,int buffersize);
	int GetInt();
	bool GetBool() { return m_spot[0] == '0'; }
};
class ConCommandArgs
{
	friend class ConCommandArgs_Single;
private:
	typedef ConCommandArgs_Single single_t;
	const char* m_refstr;
public:
	//members
	ConCommandArgs(const char* f_ref)
	{
		m_refstr = f_ref;
	}
	single_t Get(int argnum);
};
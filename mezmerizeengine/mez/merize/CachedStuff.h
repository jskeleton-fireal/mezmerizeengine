#ifndef CACHEDSTUFF_H
#define CACHEDSTUFF_H
#include "merize.h"


#define MODEL_MISSING "null.obj"
//ignore this please
class CachedStuff_baseclassDONTUSETHISPLEASE
{
public:
	virtual void error_report(int code, const char* format, ...);
	virtual const char* prettyname() { return ""; }
};

template <class Cls>
class CachedStuff : public CachedStuff_baseclassDONTUSETHISPLEASE
{
	typedef Cls* handle_t;
	typedef std::pair<stdstring, handle_t> ValPair;
	typedef stdvector<ValPair> ValVec;
	enum
	{
		CS_ERRORCODE_FALLBACKNOTFOUND = 0,
	};
private:
	ValVec m_vec;
public:
	possibly_null(handle_t) Lookup(const char* name)

	{
		for (int i = 0; i < m_vec.size(); i++)
		{
			ValPair pair = m_vec[i];
			if (!strcmp(pair.first.c_str(), name)) { return pair.second; }
		}
		const char* fb = Fallback();
		if (fb && name != fb)
		{
			Cls* fbk = Lookup(fb);
			if (fbk) return fbk;
			error_report(CS_ERRORCODE_FALLBACKNOTFOUND, name, fb);
		}
		return 0;
	}

	void Upload(const char* name, handle_t instance)
	{
		instance->m_id = m_vec.size();
		preupload(name, instance);
		m_vec.push_back(std::make_pair(name, instance));
		postupload(name, instance);
	}
	virtual void CreateDefaults() {}
	virtual const char* Fallback() { return 0; }
	virtual void setup() { CreateDefaults(); }
	virtual void  preupload(const char* name, handle_t instance) {}
	virtual void  postupload(const char* name, handle_t instance) {}

	virtual bool Exists(const char* key,int* id_storage);


	CachedStuff()
	{
		
	}
};





template<class Cls>
inline bool CachedStuff<Cls>::Exists(const char* key, int* id_storage)
{
	for (int i = 0; i < m_vec.size(); i++)
	{
		ValPair pair = m_vec[i];
		if (!strcmp(pair.first.c_str(), key)) { if (id_storage) *id_storage = i; return true; }
	}
	return false;
}


#endif
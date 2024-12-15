#ifndef CACHEDSTUFF_H
#define CACHEDSTUFF_H
#include "mez/merize/merize.h"


#define MODEL_MISSING "null.obj"
//ignore this please
class CachedStuffBase
{
public:
	virtual void error_report(int code, const char* format, ...);
	virtual const char* prettyname() { return ""; }
	typedef void* generic_handle;
	virtual generic_handle Lookup_Typeless(const char* name) = 0;
	template <class T>
	T* Lookup_Dynamic(const char* name) { return static_cast<T*>(Lookup_Typeless(name)); }
	virtual bool Exists(const char* key, int* id_storage) = 0;
};

template <class Cls>
class CachedStuff : public CachedStuffBase
{
	typedef Cls* handle_t;
	typedef std::pair<stdstring, handle_t> ValPair;
	typedef stdvector<ValPair> ValVec;
	enum
	{
		CS_ERRORCODE_FALLBACKNOTFOUND = 0,
	};
private:
	handle_t m_fallback = 0;
	ValVec m_vec;
public:
	virtual generic_handle Lookup_Typeless(const char* name) { return Lookup(name); }
	possibly_null(handle_t) Lookup(const char* name)

	{
		for (int i = 0; i < m_vec.size(); i++)
		{
			ValPair pair = m_vec[i];
			if (!strcmp(pair.first.c_str(), name)) { return pair.second; }
		}
		//not found
		if (Fallback())
		{
			//we have a fallback
			if (!m_fallback)
			{
				m_fallback = CreateFallback();
			}
			if (m_fallback) return m_fallback;
			const char* ft = Fallback();
			error_report(CS_ERRORCODE_FALLBACKNOTFOUND, name, ft);
		}
		return 0;
	}

	void Upload(const char* name, handle_t instance)
	{
		if (Fallback() && !strcmp(name, Fallback()))
		{
			m_fallback = instance;
			return;
		}
		instance->m_id = m_vec.size();
		preupload(name, instance);
		m_vec.push_back(std::make_pair(name, instance));
		postupload(name, instance);
	}\
	virtual void CreateDefaults() {}
	virtual handle_t CreateFallback() { return 0; }
	virtual const char* Fallback() { return 0; }
	virtual void setup() {  }
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
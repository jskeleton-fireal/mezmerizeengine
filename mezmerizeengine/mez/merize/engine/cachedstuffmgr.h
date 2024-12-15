#ifndef CACHEDSTUFFMGR_H
#define CACHEDSTUFFMGR_H


#include "CachedStuff.h"


//This is what is in Engine
class CachedStuffManager
{
public:
	enum
	{
		nameRModel,
		nameRTexture,
		num_of_names,
	};
	typedef int name_t;
	void load();
	CachedStuffBase* get(name_t f_name) { return m_list[f_name]; }
	~CachedStuffManager();
private:
	CachedStuffBase* m_list[num_of_names];
};
#endif
#pragma once
#include "mez/merize/merize.h"
#include "mez/merize/engine/EList.h"
#include "mez/merize/data/transform.h"
#include "mez/merize/cmp/component.h"
#include "mez/merize/cmp/componentcontainer.h"
#include "mez/merize/entityprivate/efactory.h"
#include "mez/merize/miscobjects/propobject/propobject.h"

class EDef;
class MezBaseEntity;
class EHandle;


enum
{
	LIFESTATE_DEAD,
	LIFESTATE_ALIVE,
};

class MezBaseEntity : public MezPropertyObject
{
public:
	enum MEZENTITYSTATE
	{
		MEZENTSTATE_INVALID_STATE, //Doesnt do anything on updates.
		MEZENTSTATE_INITIALIZE_NEEDED, //Calls Initialize on updates.
		MEZENTSTATE_INITIALIZING, 
		MEZENTSTATE_READY, //Calls Update on updates
	};
public:
	//id in the edef. gets updated on Spawn()
	int m_DefId = ENTITY_INVALID_DEFID;
	//hidden id to prevent ehandle clashing. gets updated on Spawn()
	short m_InternalId = -1;
	//Should this be public?
	//dont change this to a u16, no matter how tempting it is
	MEZENTITYSTATE m_State;

	ComponentContainer m_ComponentContainer;

	bool m_DeleteMe = 0;
public:
	void Spawn();
	EDef* GetDef();
	void Destroy();
	EHandle GetEHandle();
	template <class T>
	T* Cast() { return dynamic_cast<T*>(this); }
public:
	virtual void Update() {}
	virtual void Pre_Update() {}
	virtual void Post_Update() {}
	virtual void Initialize() {}
public:
	inline void Update_Calls()
	{
		Pre_Update();
		Update();
		Post_Update();
	}
	virtual bool HandleStates();
public:
	virtual const char* GetClassname() = 0;
	static MezBaseEntity* Find_Typeless(const char* f_classname);
	template <class T>
	static T* Find(const char* f_classname) { return dynamic_cast<T*>(Find_Typeless(f_classname)); }
};

#include "EHandle.h"
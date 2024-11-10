#pragma once
#include "../merize.h"

//displaynames are disabled in release builds
#define COMPONENT_DISPLAYNAMES_ENABLED _DEBUG

#define COMPONENT_CREATEDISPLAYNAME(vDis) vDis

#if COMPONENT_DISPLAYNAMES_ENABLED
#define COMPONENT_SETDISPLAYNAME(vDisplayName) virtual const char* DisplayName() {return COMPONENT_CREATEDISPLAYNAME(vDisplayName);}
#else
#define COMPONENT_SETDISPLAYNAME(vDisplayName) //inherit from base
#endif
#define COMPONENT_DEFINE(vInternalName,vDisplayName) virtual const char* InternalName() {return vInternalName;} COMPONENT_SETDISPLAYNAME(vDisplayName)
class ComponentContainer;

class MezComponent_Transform;
class MezComponent_Renderable;

class MezComponent : public MezPropertyObject
{
public:
	ComponentContainer* m_parent;
public:
	//keep these AS SMALL and CONCISE as possible. they are used for component type searching
	virtual const char* InternalName() = 0;
	//used for debugging
	virtual const char* DisplayName() { return "?"; }

	virtual void Initialize() {}

	virtual void Deletion() {}

public:
	//for communicating to the container.
	virtual void Container_ComponentWasAdded(MezComponent* f_component) {}
	//virtual void Container_ComponentWasRemoved(MezComponent* f_component) {}
protected:
	MezComponent* FindComponent(const char* f_internal_name);
	MezComponent_Transform* FindTransform();
	MezComponent_Renderable* FindRenderable();

protected:
	virtual void DeclareProperties(PropertyContainer* vector);
};

#define COMPONENT_INTERNAL_NAME_TRANSFORM "t"
#define COMPONENT_INTERNAL_NAME_RENDERABLE "r"


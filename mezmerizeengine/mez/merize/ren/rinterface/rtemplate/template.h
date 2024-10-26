#pragma once

//for rinterface. some template classes for varying stuff.
//(ex: RTemplate_3D for pvm stuff, RTemplate_3DLighting for pvm + lighting)


//the original rtemplate class
class RTemplate
{
public:
	virtual void ProgramUsed(class RInterface* f_rinterface) = 0;
	virtual void Invalidate(class RInterface* f_rinterface) = 0;
};

//new rtemplate class. inehrit from this
template <class ClassThatInheritsRInterface>
class RTemplate_2 : public RTemplate
{
private:
#define rtemplate2_cpyfunc(vFuncName) virtual void vFuncName(class RInterface* f_rinterface) { vFuncName(dynamic_cast<ClassThatInheritsRInterface*>(f_rinterface)); } 	virtual void vFuncName(ClassThatInheritsRInterface* f_rinterface) = 0;
public:
	//ignore this.. just pretend these are the same as RTemplate's funcs
	rtemplate2_cpyfunc(ProgramUsed);
	rtemplate2_cpyfunc(Invalidate);

};



#pragma once

//for rinterface. some template classes for varying stuff.
//(ex: RTemplate_3D for pvm stuff, RTemplate_3DLighting for pvm + lighting)


//the original rtemplate class
class RTemplate
{
public:
	virtual void ProgramUsed(class RInterface* f_rinterface) = 0;
	//todo: need a Invalidate virtual in case the shader changes
};

//new rtemplate class. inehrit from this
template <class ClassThatInheritsRInterface>
class RTemplate_2 : public RTemplate
{
public:
	virtual void ProgramUsed(class RInterface* f_rinterface) { ProgramUsed(dynamic_cast<ClassThatInheritsRInterface*>(f_rinterface)); }
	virtual void ProgramUsed(ClassThatInheritsRInterface* f_rinterface) = 0;


};



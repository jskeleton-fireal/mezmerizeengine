#pragma once
#include "../../../merize.h"

typedef unsigned int glint_t;
class GLShader
{
public:
	glint_t m_shader;
	void LoadFromFile(const char* filename);

	//note: since vLoad gets called in LoadFromFile, and it is virtual, we cannot make a constructor here.
	//i remember there being a way around this but i dont care rn

protected:
	virtual bool vLoad(const char* f_file) = 0;
};
class GLShaderVertex : public GLShader
{
public:
	GLShaderVertex(const char* f_fn) { LoadFromFile(f_fn); }
protected:
	virtual bool vLoad(const char* f_file);
};

class GLShaderFragment : public GLShader
{
public:
	GLShaderFragment(const char* f_fn) { LoadFromFile(f_fn); }
protected:
	virtual bool vLoad(const char* f_file);
};

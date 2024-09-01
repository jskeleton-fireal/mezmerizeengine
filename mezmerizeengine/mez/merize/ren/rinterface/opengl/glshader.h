#pragma once


class GLShader
{
public:
	GLint m_shader;
	void LoadFromFile(const char* filename);

	GLShader(const char* f_fn) { LoadFromFile(f_fn); }

protected:
	virtual bool vLoad(const char* f_file) = 0;
};
class GLShaderVertex : public GLShader
{
public:
protected:
	virtual bool vLoad(const char* f_file);
};

class GLShaderFragment : public GLShader
{
public:
protected:
	virtual bool vLoad(const char* f_file);
};

struct GLShader_Pair
{
	GLShaderVertex m_vertex;
	GLShaderFragment m_frag;
};
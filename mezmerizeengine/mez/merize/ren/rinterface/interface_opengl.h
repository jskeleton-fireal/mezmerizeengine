
#ifndef INTERFACE_OPENGL
#define INTERFACE_OPENGL
#include "rinterface.h"

#define RIF_GL_DISABLED -1

enum
{
	RIF_VAO_GL_POSITION = 0,
};

typedef u32 glint_t;

class RInterface_OpenGL : public RInterface
{
public:
	RINTERFACE_DEFINE_STATIC_FUNCS;
public:
	virtual void Initialize();
	virtual void UploadVerts(Vector verts[],int count = -1);
	virtual void UploadShader(int shader_id);
	virtual void Prepare();//set schtuff
	virtual void Draw();
	virtual void PostDraw();//reset stuff set by prepare


	glint_t m_vertcount;
	glint_t m_ShaderProgram = RIF_GL_DISABLED;
	glint_t m_VertexBuffer = RIF_GL_DISABLED;
	glint_t m_VAO = RIF_GL_DISABLED;
};

#endif
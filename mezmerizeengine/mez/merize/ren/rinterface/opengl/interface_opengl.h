
#ifndef INTERFACE_OPENGL
#define INTERFACE_OPENGL
#include "../rinterface.h"

//Not used atm

#define RIF_GL_DISABLED 0xFFFFFFFF // 4294967295
#define RIF_ISENABLED(vVal) ((vVal+1))
#define RIF_ISDISABLED(vVal) !(RIF_ISDISABLED(vVal))

enum
{
	RIF_VAO_GL_POSITION = 0,
};

typedef u32 glint_t;


class RInterface_OpenGL : public RInterface
{
public:
	virtual void Initialize();
	virtual void UploadVerts(Vector verts[],int count = -1);
	virtual void UploadShader(int shader_id);
	virtual void UploadShader(const char* vertexshader,const char* fragmentshader);
	virtual void Prepare();//set schtuff
	virtual void Draw();
	virtual void PostDraw();//reset stuff set by prepare


	glint_t m_vertcount=-1;
	glint_t m_ShaderProgram;
	glint_t m_VertexBuffer;
	glint_t m_VAO;
};

#endif
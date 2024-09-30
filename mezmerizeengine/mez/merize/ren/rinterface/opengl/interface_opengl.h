
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

class GLShader;
class RInterface_OpenGL : public RInterface
{
	//todo: virtuals got updated. need to move to base class
public:
	virtual void Initialize();
	virtual void UploadVerts(Vector verts[],int count = -1);
	//not implemented. dont use this.
	virtual void UploadShader_Id(int shader_numeric_id);
	//uploads a FRAGMENT shader to the shader program. USE LinkShaderProgram() when you finished uploading!!!!
	virtual void UploadShader(const char* shader_id);
	//uploads a VERTEX shader to the shader program.
	virtual void UploadShader_Vertex(const char* shader_id);
	//ysed in uploadshader.. may be useful externally?
	void AttachShader(GLShader* shader);
	//CALL THIS when you finished w shader schtuff.
	//note: probably should be renamed for other apis or somethign
	virtual void LinkShaderProgram();
	virtual void Prepare();//set schtuff
	virtual void Draw();
	virtual void PostDraw();//reset stuff set by prepare

	virtual void SetDrawMode(RModel_Mesh::MESH_DRAWMODE mode) { m_drawmode = mode; }

	glint_t m_vertcount=-1;
	glint_t m_ShaderProgram;
	glint_t m_VertexBuffer;
	glint_t m_VAO;
	int m_drawmode;
};

#endif
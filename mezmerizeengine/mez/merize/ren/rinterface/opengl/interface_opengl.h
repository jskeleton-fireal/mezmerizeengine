
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
	RIF_VAO_GL_NORMAL = 1,
	RIF_VAO_GL_UV = 2,
};

typedef u32 glint_t;

class GLShader;
class RInterface_OpenGL : public RInterface
{
	//todo: virtuals got updated. need to move to base class
public:
	virtual void Initialize();
	virtual void UploadVerts(Vector verts[],int count = -1);
	virtual void UploadNormals(Vector normals[], int count = -1);
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

	virtual void RegenerateProgram();

	virtual void UploadTexture(class RTextureBase* f_texture, int f_index);
	virtual void UploadUVs(struct Vector f_uvs[], int f_count);
	virtual void UploadTexture_Name(const char* f_name, int f_index = 0);

	virtual void Prepare();//set schtuff
	virtual void Draw();
	virtual void PostDraw();//reset stuff set by prepare

	virtual void SetDrawMode(RModelMeshSingle::MESH_DRAWMODE mode) { m_drawmode = mode; }

	virtual void RequestFeature(rinterface_feature_t feature);

	glint_t m_vertcount=-1;
	glint_t m_ShaderProgram;
	glint_t m_VertexBuffer;

	glint_t m_VAO; //position
	glint_t m_VAO_normal = -1; //normals
	glint_t m_VAO_uv = -1; //uvs

	glint_t m_Texture1 = -1;

	int m_drawmode;
};

#endif
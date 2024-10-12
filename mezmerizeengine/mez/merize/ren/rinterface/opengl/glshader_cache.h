#pragma once

#include "../../../merize.h"
#include "glshader.h"
#include "../../../staticdefs.h"
#include "../../../helpers/mezstring.h"

//shader id = "default"
//shader filename = "default.vert.txt"

//shaders are searched from starting in content/shader

class GLShaderCache
{
public:
	//this needs to be public for static stuff to access it
	struct GLShaderCache_Stored
	{
		u32 m_shadertype;
		mezstring_t m_sid;
		GLShader* m_shader;
		void free()
		{
			delete m_shader;
			m_shader = 0;
		}
	};

	enum GLShaderType
	{
		GLSHADERTYPE_UNKNOWN,
		GLSHADERTYPE_VERTEX,
		GLSHADERTYPE_FRAGMENT,
	};
private:
	stdvector< GLShaderCache::GLShaderCache_Stored> m_storage;
public:
	//GLShader_Pair* Lookup_iId(int f_id);
	GLShader* Lookup_sId(const char* f_sid, GLShaderType f_type);

	//load every shader in the shaders folder. not implemented
	void LoadAllAvailableShaders();

	GLShaderType DetermineShaderTypeFromFilename(const char* f_filename);
	mezstring_t GetShaderFilenameFromId(const char* f_id, GLShaderType f_type);
	mezstring_t GetShaderIdFromFilename(const char* f_filename, GLShaderType* f_type = 0);
	bool LoadShader(const char* f_filename);

	void NeedShader(const char* f_shaderid);

	void wipe()
	{
		for (int i = 0; i < m_storage.size(); i++)
		{
			m_storage[i].free();
		}
		m_storage.clear();
	}

private:
	GLShader* lookupshaderincache(const char* f_sid, GLShaderCache::GLShaderType f_type);
};
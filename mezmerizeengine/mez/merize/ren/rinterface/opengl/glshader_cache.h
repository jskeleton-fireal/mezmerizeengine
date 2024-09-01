#pragma once

#include "../../../merize.h"
#include "glshader.h"

class GLShaderCache
{
public:
	//this needs to be public for static stuff to access it
	struct GLShaderCache_Stored
	{
		const char* m_id;
		GLShader_Pair m_pair;
	};
private:
	stdvector< GLShaderCache::GLShaderCache_Stored> m_storage;
public:
	GLShader_Pair* Lookup(int f_id);
};
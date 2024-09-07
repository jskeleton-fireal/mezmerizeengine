#include "glshader_cache.h"
#include "../../../merize.h"
#include "../../../console/cmd.h"

const char* thewordfrag = "frag";
const char* thewordvert = "vert";

GLShader* GLShaderCache::lookupshaderincache(const char* f_sid, GLShaderCache::GLShaderType f_type)
{
	for (int i = 0; i < m_storage.size(); i++)
	{
		GLShaderCache_Stored* it = &m_storage[i];
		if (it->m_shadertype != f_type) continue;
		if (strcmp(it->m_sid, f_sid)) continue;

		return it->m_shader;
	}
	return nullptr;
}

GLShader* GLShaderCache::Lookup_sId(const char* f_sid, GLShaderCache::GLShaderType f_type)
{
	GLShader* shader = lookupshaderincache(f_sid, f_type);
	if (shader) return shader;

	//..alright now try to see if this shader even exists
	static_format_t fn = GetShaderFilenameFromId(f_sid, f_type);
	bool r = LoadShader(fn.buffer);
	if (!r)
	{
		//Oh.
		console_printf("warning: attempt to use nonexistant shader: %s. this will cause issues!\nExpected Filename:%s\n", f_sid,fn.buffer);
		
		//todo: need some fallback shaders

		return 0;
	}

	console_printf("warning: shader %s was not cached. mark shaders as needed please\n", fn.buffer);

	shader = lookupshaderincache(f_sid, f_type);
	if (!shader)
	{
		//shouldnt happen but im stupid
#if _DEBUG
		console_printf("ERROR: SHADER %s FAILED TO BE ASSIGNED!!\n",fn.buffer);
		assert(0);
#endif
	}
	return shader;
}

void GLShaderCache::LoadAllAvailableShaders()
{
}

bool GLShaderCache::LoadShader(const char* f_filename)
{ 
	GLShaderType type;
	static_format_t sid = GetShaderIdFromFilename(f_filename, &type);
	GLShaderCache_Stored pair = GLShaderCache_Stored();
	pair.m_shadertype = type;
	pair.m_sid = sid;
	GLShader* l_shader = 0;
	//Im not making a factory system for two types
	switch (type)
	{
	case GLSHADERTYPE_FRAGMENT: l_shader = new GLShaderFragment(f_filename); break;
	case GLSHADERTYPE_VERTEX: l_shader = new GLShaderVertex(f_filename); break;
	}
	if (l_shader->m_state)
	{
		//bad
		return false;
	}
	pair.m_shader = l_shader;
	m_storage.push_back(pair);
	return 1;
}
static_format_t GLShaderCache::GetShaderIdFromFilename(const char* f_filename, GLShaderType* f_type /*= 0 */)
{
	//find the last / or \ in the filename (note: not sure how macos handles filenames.. ik linux works)
	const int len = strlen(f_filename);
	//length must be greater than 4 to make sure its a valid path
	//must be less than 400 so static format buffers dont freak out
	if (len < 4 || len > 400) { goto label_badfile; }
	//scope is needed here for goto to work
	{
		int whereitstarts = -1;
		int whereitends = 0;
		for (int i = 0; i < len; i++)
		{
			if (f_filename[i] == '/' || f_filename[i] == '\\') whereitstarts = i+1;
			if (f_filename[i] == '.' && !whereitends)
			{
				whereitends = i;
				switch (f_filename[i + 1])
				{
				case 'f': if (f_type) *f_type = GLSHADERTYPE_FRAGMENT; break;
				case 'v': if (f_type) *f_type = GLSHADERTYPE_VERTEX; break;
				default: goto label_badfile; break;
				}
			}
		}
		if (whereitstarts == -1 || !whereitends) goto label_badfile;

		//okay. copy it
		static_format_t formato = static_format_t();
		formato.buffer[len] = 0;
		memcpy(formato.buffer, f_filename + whereitstarts, len - whereitends);
		return formato;
	}

label_badfile:
	if (f_type) *f_type = GLSHADERTYPE_UNKNOWN;
	return static_format("\0");
}

static_format_t GLShaderCache::GetShaderFilenameFromId(const char* id, GLShaderType f_type)
{
	const char* ptrtotext = f_type == GLSHADERTYPE_FRAGMENT ? thewordfrag : thewordvert;
	return static_format("content/shader/%s.%s.txt",id,ptrtotext);
}



GLShaderCache::GLShaderType GLShaderCache::DetermineShaderTypeFromFilename(const char* f_filename)
{
	if (!strcmp(f_filename, ".frag.txt")) return GLSHADERTYPE_FRAGMENT;
	if (!strcmp(f_filename, ".vert.txt")) return GLSHADERTYPE_VERTEX;
	return GLShaderCache::GLSHADERTYPE_UNKNOWN;
}

#include "mez/merize/entity/EntityPhysical.h"
#include "mez/merize/engine/CachedStuff.h"
#include <mez/merize/ren/rinterface/rinterface.h>
#include <mez/merize/ren/tex/texture.h>
class TstTestImplementation : public MezEntityPhysical
{
public:
	DECLARE_ENTITY(TstTestImplementation);
public:
	TstTestImplementation() {  }
public:
	RTexture* tex;
	virtual void Initialize()
	{
		MezEntityPhysical::Initialize();
		InitModel("36.obj");
#if 0
#if 1
		MezColor color1 = MezColor(0xff0000);
		MezColor color2 = MezColor(0x00ff00);
		tex = RTexture::CreateRGBA8Texture(2, 1);
		tex->m_rawtexture.rgba[0] = color1;
		tex->m_rawtexture.rgba[1] = color2;
#else
		tex = RTexture();
		tex.m_Height = 64;
		tex.m_Width = 64;
		tex.m_Format = RTexture::TextureFormat::RGB8;
		
		tex.m_rawtexture.raw = reintrp_noderef(this, byte*);
#endif
		tex->m_flags = tex->point_filter;
		m_ComponentContainer.FindRenderable()->m_Renderable->m_rInterface->UploadTexture(tex);
#endif
		SetShader("modifiedphong", "default3d");
		SetLighting(true);
		GetTransform()->m_Position.z = -4;
		//for msvc debugger
		RModel_Base* mesh = m_ComponentContainer.FindRenderable()->m_Renderable->m_model;
		int uv_count = mesh->GetVertCount();
		Vector* uvs = mesh->GetUVs();
		uvs = uvs;
	}

	~TstTestImplementation()
	{
		tex->free();
	}

	virtual void Update()
	{
		float time = engine->time * 1.2f;
		float time2 = engine->time * 80.0f;
		Vector v = Vector(sinf(time), sinf(time / -8.0f), cosf(time)).normalize();
		engine->rendersys.enviro_sky.get()->m_sun = v;
	}

};

ENTITY_LINK(PROJECT_TESTING,"test_imp", TstTestImplementation);
#ifndef ENGINE_H
#define ENGINE_H
#include "EList.h"
#include "ren/RenderSystem.h"
#include "cachedstuffmgr.h"
#include "console/conhelper.h"

struct EngineLaunchParameters
{
	bool m_textmode = 0;
};

struct EngineVersion
{
	friend class Engine;
public:
	u16 m_major;
	u16 m_minor;
	u32 m_build;
private:
	//These should only be called internally by the engine
	const char* tostring();
};
extern EngineVersion engine_version;
namespace sf
{
	class Window;
	class RenderWindow;
}
#define RENDER_WINDOW_CLASS sf::Window

enum ENGINE_MSGBOXTYPE_T
{
	ENGINE_MSGBOXTYPE_ERROR = 0x1,
	ENGINE_MSGBOXTYPE_QUESTIONMARK = 0x2, //dont use
	ENGINE_MSGBOXTYPE_WARNING = 0x3,
	ENGINE_MSGBOXTYPE_INFORMATION = 0x4,
};
class Engine;
extern Engine* engine;

class Engine
{
	friend RenderSystem;
public:
	EList elist; //huge
	RenderSystem rendersys;
	int m_id;
	CachedStuffManager cache;
	ConsoleHelper conhelper;
private:
	EngineLaunchParameters m_launchparameters = EngineLaunchParameters();
public:
#pragma warning (push)
#pragma warning (disable: 26495)
	Engine(EngineLaunchParameters launchparams);
	Engine() { eng_initialize(); }
private:
	void eng_initialize();
#pragma warning (pop)
public:
	int run();
	void fatalmsg(const char* msg);
	void show_messagebox(const char* f_msg, ENGINE_MSGBOXTYPE_T f_type);
private:
	void update();
	void render();
	void updateloop_win();
	void updateloop_txt();

	trustmeptr(RENDER_WINDOW_CLASS) m_Window;
public:
	//call this in main.cpp or similar
	static int RunEngine();

public:
	//public functions for everyone
	MezBaseEntity* CreateEntityByName_Typeless(const char* m_name);
	template <class TYPE>
	TYPE* CreateEntityByName(const char* m_name)
	{
		return dynamic_cast<TYPE*>(reinterpret_cast<MezBaseEntity*>(CreateEntityByName_Typeless(m_name)));
	}
};


#endif
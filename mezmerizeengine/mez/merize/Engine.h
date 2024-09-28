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
	//Sometimes, we need the main thread to execute something because another thread cant access something.
	//An immediate operation gets called before the engine internally updates the game state
	//not sure how good this is in a security context.. one bad buffer overflow and boom rca right there with this
	voidfunction_t* m_immediate_operation = 0;

	float time = 0.0f;
	u64 time_alt;
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
	void push_immediate_operation(voidfunction_t& function);
	void reset_globals();
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
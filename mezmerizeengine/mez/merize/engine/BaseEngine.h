#ifndef ENGINE_H
#define ENGINE_H
#include "EList.h"
#include "mez/merize/ren/RenderSystem.h"
#include "mez/merize/engine/cachedstuffmgr.h"
#include "mez/merize/console/conhelper.h"

struct EngineLaunchParameters
{
	bool m_textmode = 0;
};

struct EngineVersion
{
	friend class BaseEngine;
public:
	const char* tostring();
	int tonumeric();
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
class BaseEngine;
extern BaseEngine* engine;

class BaseEngine
{
	friend RenderSystem;
public:
	EList elist; //huge
	RenderSystem rendersys;
	int m_id;
	CachedStuffManager cache;
	ConsoleHelper* conhelper;
	voidfunction_t* m_immediate_operation = 0;

	float time = 0.0f;
	u64 time_alt;
	float time_delta;
	bool active = false;
protected:
	EngineLaunchParameters m_launchparameters = EngineLaunchParameters();
private:
	class EngineSuperSecret* m_supersecret;
public:
#pragma warning (push)
#pragma warning (disable: 26495)
	BaseEngine(EngineLaunchParameters launchparams);
	BaseEngine() { eng_initialize(); }
private:
	void eng_initialize();
#pragma warning (pop)
public:
	int run();
	void fatalmsg(const char* msg);
	void show_messagebox(const char* f_msg, ENGINE_MSGBOXTYPE_T f_type);
	void push_immediate_operation(voidfunction_t& function);
	void reset_globals();
	//force stop
	void stop();
private:
	void update();
	void render();
	void updateloop_win();
	void updateloop_txt();
	void render_setup();
	RENDER_WINDOW_CLASS* m_Window;
public:
	//dont use this anymore.
	static int RunEngine();

	//for whitewater/wisconsin
	void* GetWindowHandle();
public:
	//public functions for everyone
	MezBaseEntity* CreateEntityByName_Typeless(const char* m_name);
	template <class TYPE>
	TYPE* CreateEntityByName(const char* m_name)
	{
		return dynamic_cast<TYPE*>(reinterpret_cast<MezBaseEntity*>(CreateEntityByName_Typeless(m_name)));
	}
	//run a commmand as if it were typed at the console
	bool RunCommand(const char* cmd);
public:
	//virtuals
	virtual const char* GetVersion_String() { return "v0.1"; } //Versions may be better as their own class instead of this
	virtual int GetVersion_Numeric();
	virtual const char* GetName() { return "mezmerize instance"; }
	virtual const char* GetTitle() { return GetName(); }


	virtual bool ProjectIdIsValid(u64 f_id) { return f_id == PROJECT_MEZMERIZE; }
protected:
	//some hidden functions :)
	class EngineConsole* GetEngineConsole();
	//more virtuals. to be overridden by whoever inherits this
	virtual void OnInitialized() {}
	virtual void OnPreInitialized() {}

	class ConBall GetConBall();
	class EntBall GetEntBall();
	//override these if you dont like balls
	virtual void UnpackConBall();	
	virtual void UnpackEntBall();
public:
	RInterface* create_rinterface_instance();
	RStatic* create_rstatic();

	void cursorlock_status(bool* setval);
	void set_mousepos(Vector2 f_pos);
};


typedef BaseEngine Engine_Mez;

#endif
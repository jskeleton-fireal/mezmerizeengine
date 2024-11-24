
#include "BaseEngine.h"
#include <SFML/Graphics.hpp>
//TODO: need to use gtk
#include <Windows.h>
#include "mez/merize/version.h"
#include <stdio.h>
#include <iostream>
#include "mez/merize/helpers/static_format.h"
#include "eng_console.h"
#include "mez/merize/entityprivate/efactory.h"
#include "mez/merize/ren/rinterface/rstatic.h"
#include "mez/merize/io/input.h"


//holy what a mess

//this system sucks
#define ALLOW_RENDERING RENDERABLE_MODE || m_launchparameters.m_textmode
#define FORBID_RENDERING !(ALLOW_RENDERING)

BaseEngine* engine;
EngineVersion engine_version;
#pragma warning (push)
#pragma warning (disable: 26495)
BaseEngine::BaseEngine(EngineLaunchParameters launchparams)
{
	m_launchparameters = launchparams;
    eng_initialize();
}
void BaseEngine::eng_initialize()
{
    m_id = 0;
#if SUPPORT_MULTIPLE_ENGINES
    static int s_engine_counter = 0;
    m_id = s_engine_counter;
    s_engine_counter++;
#endif
}
#pragma warning (pop)

struct console_thread_pass
{
    BaseEngine* m_engine;
    RENDER_WINDOW_CLASS* m_window;
    EngineConsole* m_console;
};

void console_thread(console_thread_pass f_pass)
{
    while (f_pass.m_window->isOpen())
    {
        f_pass.m_console->process(f_pass.m_engine);
    }
}

class EngineSuperSecret
{
public:
    sf::Clock* clockp;
    EngineConsole console;
};



int BaseEngine::run()
{
    //
    typedef void (BaseEngine::* updateloop)();

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "mezmerize");
    m_Window = &window;

    if (FORBID_RENDERING)
    {
        //bug: window flashes for a very small amount of time using this
        ::ShowWindow(window.getSystemHandle(), SW_HIDE);
    }
    else
    {
#if !_DEBUG
        //hide the console
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif
    }
    m_supersecret = new EngineSuperSecret();
    //using function pointers here to avoid ugly if statement
    updateloop upd;

    //this is ugly.. but hey this is init so whatever
    if (FORBID_RENDERING)
    {
        upd = &BaseEngine::updateloop_txt;
    }
    else
    {
        upd = &BaseEngine::updateloop_win;

    }


    const char* enginever = engine_version.tostring();
    printf("mezmerize version %s\n", enginever);
    //print the name of the engine
    printf("%s %s\n", this->GetName(), this->GetVersion_String());
    std::cout << "build: " << BUILD_DATE << "," << BUILD_TIME << "\n";


    engine = this;
    if (ALLOW_RENDERING)
    {
        render_setup();
    }
   
    console_thread_pass pass = { this,m_Window,&m_supersecret->console };
    sf::Thread cthread(&console_thread, pass);
    cthread.launch();
    //load cache house

    //yes. this needs to be called regardless of rendering setting.
    cache.m_models.setup();
    //not sure abt this onr though
    cache.m_textures.setup();
    sf::Clock clock; // starts the clock
    m_supersecret->clockp = &clock;
    OnInitialized();
    //THIS IS THE LOOP!!!
    while (window.isOpen())
    {
        Input::tic();
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            //this may need to be changed to a switch statement later
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                break;
            }
            if (event.type == sf::Event::Resized)
            {
                rendersys.m_viewport_size.x = event.size.width;
                rendersys.m_viewport_size.y = event.size.height;
                rendersys.notify_vpupdate();
                break;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                Input::notify_key_pressed(event.key.scancode);
                break;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                Input::notify_key_released(event.key.scancode);
                break;
            }

        }


        engine = this;
        if (m_immediate_operation)
        {
            m_immediate_operation();
            m_immediate_operation = 0;
        }

        float old_time = time;
        time = clock.getElapsedTime().asSeconds();
        time_alt = clock.getElapsedTime().asMicroseconds();
        time_delta = time - old_time;
        //update
        (this->*upd)();

        // Update the window
        //window.display();
    }
    if (window.isOpen())
    {
        window.close();
    }

    cthread.terminate();
    return EXIT_SUCCESS;
}

void BaseEngine::fatalmsg(const char* msg)
{
    //todo: use gtk to show an error message or something
#if _DEBUG
    show_messagebox(msg, ENGINE_MSGBOXTYPE_ERROR);
#endif
    abort();
}
//#1 is question which is deprecated by windows
const char* msgbox_descr[] = {"Error","","Warning","Information"};

void BaseEngine::show_messagebox(const char* f_msg, ENGINE_MSGBOXTYPE_T f_type)
{
    printf(f_msg);
    int r = MessageBoxA(m_Window->getSystemHandle(), f_msg, static_format("Engine - %s",msgbox_descr[f_type-1]), f_type << 4);
}

void BaseEngine::push_immediate_operation(voidfunction_t& function)
{
    assert(!m_immediate_operation);
    if (m_immediate_operation) { abort(); }
    m_immediate_operation = function;
}

void BaseEngine::reset_globals()
{
    this->m_supersecret->clockp->restart();
}

void BaseEngine::update()
{
    elist.update();
}

void BaseEngine::render()
{
    rendersys.Render_CallThisInEnginePlease();
}

void BaseEngine::updateloop_win()
{
    update();
    render();
}

void BaseEngine::updateloop_txt()
{
    update();
}

void BaseEngine::render_setup()
{
    rendersys.Engine_Setup(m_Window);
    rendersys.m_viewport_size = Vector2(800,600);
    rendersys.notify_vpupdate();
}

int BaseEngine::RunEngine()
{
    BaseEngine* engine = new BaseEngine();
    int c = engine->run();
    delete engine;
    return c;
}

MezBaseEntity* BaseEngine::CreateEntityByName_Typeless(const char* m_name)
{
    efactory_t* f = entity_factories_t::find(m_name);
    if (!f) return 0;
    return f->m_func();
}

bool BaseEngine::RunCommand(const char* cmd)
{
    m_supersecret->console.process_single(this,cmd);
    return false;
}

EngineConsole* BaseEngine::GetEngineConsole()
{
    return &this->m_supersecret->console;
}

#pragma warning (disable: 4172)
const char* EngineVersion::tostring()
{
    return MEZ_VERSION;
}

int EngineVersion::tonumeric()
{
    return MEZ_VERSION_NUMERIC;
}

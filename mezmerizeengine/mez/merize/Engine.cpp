
#include "Engine.h"
#include <SFML/Graphics.hpp>
//TODO: need to use gtk
#include <Windows.h>
#include "../version.h"
#include <stdio.h>
#include <iostream>
#include "helpers/static_format.h"
#include "eng_console.h"
#include "entityprivate/efactory.h"


//this system sucks
#define ALLOW_RENDERING RENDERABLE_MODE || m_launchparameters.m_textmode
#define FORBID_RENDERING !(ALLOW_RENDERING)

Engine* engine;
EngineVersion engine_version = { VERSION_MAJOR,VERSION_MINOR,VERSION_BUILD };
#pragma warning (push)
#pragma warning (disable: 26495)
Engine::Engine(EngineLaunchParameters launchparams)
{
	m_launchparameters = launchparams;
    eng_initialize();
}
void Engine::eng_initialize()
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
    Engine* m_engine;
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
sf::Clock* clockp;

int Engine::run()
{
    //
    typedef void (Engine::* updateloop)();

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

    //using function pointers here to avoid ugly if statement
    updateloop upd;

    //this is ugly.. but hey this is init so whatever
    if (FORBID_RENDERING)
    {
        upd = &Engine::updateloop_txt;
    }
    else
    {
        upd = &Engine::updateloop_win;

    }
    const char* enginever = engine_version.tostring();
    printf("mez: %s\n", enginever);
    std::cout << "build: " << BUILD_DATE << "," << BUILD_TIME << "\n";

    engine = this;
    if (ALLOW_RENDERING)  rendersys.Engine_Setup(m_Window);
   
    EngineConsole econ = EngineConsole();
    console_thread_pass pass = { this,m_Window,&econ };
    sf::Thread cthread(&console_thread, pass);
    cthread.launch();
    //load cache house

    cache.m_models.setup();
    sf::Clock clock; // starts the clock
    clockp = &clock;
    //THIS IS THE LOOP!!!
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }


        engine = this;
        if (m_immediate_operation)
        {
            m_immediate_operation();
            m_immediate_operation = 0;
        }

        time = clock.getElapsedTime().asSeconds();
        time_alt = clock.getElapsedTime().asMicroseconds();
        //update
        (this->*upd)();

        // Update the window
        //window.display();
    }

    return EXIT_SUCCESS;
}

void Engine::fatalmsg(const char* msg)
{
    //todo: use gtk to show an error message or something
#if _DEBUG
    show_messagebox(msg, ENGINE_MSGBOXTYPE_ERROR);
#endif
    abort();
}
//#1 is question which is deprecated by windows
const char* msgbox_descr[] = {"Error","","Warning","Information"};

void Engine::show_messagebox(const char* f_msg, ENGINE_MSGBOXTYPE_T f_type)
{
    printf(f_msg);
    int r = MessageBoxA(m_Window->getSystemHandle(), f_msg, static_format("Engine - %s",msgbox_descr[f_type-1]), f_type << 4);
}

void Engine::push_immediate_operation(voidfunction_t& function)
{
    assert(!m_immediate_operation);
    if (m_immediate_operation) { abort(); }
    m_immediate_operation = function;
}

void Engine::reset_globals()
{
    clockp->restart();
}

void Engine::update()
{
    elist.update();
}

void Engine::render()
{
    rendersys.Render_CallThisInEnginePlease();
}

void Engine::updateloop_win()
{
    update();
    render();
}

void Engine::updateloop_txt()
{
    update();
}

int Engine::RunEngine()
{
    Engine* engine = new Engine();
    int c = engine->run();
    delete engine;
    return c;
}

MezBaseEntity* Engine::CreateEntityByName_Typeless(const char* m_name)
{
    efactory_t* f = entity_factories_t::find(m_name);
    if (!f) return 0;
    return f->m_func();
}

#pragma warning (disable: 4172)
const char* EngineVersion::tostring()
{
    char buffer[300];
    sprintf_s(buffer, "%04x.%04x.%08x", engine_version.m_major, engine_version.m_minor, engine_version.m_build);
    return buffer;
}

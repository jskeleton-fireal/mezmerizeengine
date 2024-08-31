#pragma once


class Engine;
class EngineConsole
{
public:
	void process(Engine* f_engine);
private:
	void process_single(Engine* f_engine,const char* input);
};


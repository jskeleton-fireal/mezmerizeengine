#pragma once


class BaseEngine;
class EngineConsole
{
public:
	void process(BaseEngine* f_engine);
private:
	void process_single(BaseEngine* f_engine,const char* input);
};


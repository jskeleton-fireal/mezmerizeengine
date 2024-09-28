#pragma once
#include "gl_def.h"


#define GLDEBUGHELP_ACTIVE 1

//only include this file if you NEED it,. MEAN IT!! (make sure this is C EXTERN BTW)

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);

//call during init
void gldebughelpSETUPNOW();


void _glCheckForErrorPlease(const char* file, int line);

#define glCheckForError() _glCheckForErrorPlease(__FILE__,__LINE__)

const char* glerrortostring(int error_code);
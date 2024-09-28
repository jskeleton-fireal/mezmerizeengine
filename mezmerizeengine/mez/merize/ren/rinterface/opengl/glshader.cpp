#include "glshader.h"
#include <fstream>
#include "gl_def.h"
#include "../../../console/cmd.h"

void GLShader::LoadFromFile(const char* filename)
{
    m_state = 9;
    std::ifstream file;
    file.open(filename);
    assert(file.good());

    char buffer[0x400];
    //BAD!!!!! BAD BAD BAD!!! THIS IS REALLY BAD!!!!
    memset(buffer, 0, 0x400);

    file.read(buffer, 0x400);


    bool res = vLoad(buffer);
    if (!res) return;
    //Trust me bro
    const GLchar* glstring = reinterpret_cast<const GLchar*>(buffer);
    glShaderSource(m_shader, 1, &glstring, NULL);
    m_state = 0 ;
    glCompileShader(m_shader);
    //error checking. include this in release too!
    {
        int  success;
        char infoLog[512];
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(m_shader, 512, NULL, infoLog);
            console_printf("Shader compile failed!\n\n\n%s\n", infoLog);
        }
    }

    file.close();
}

bool GLShaderVertex::vLoad(const char* f_file)
{
    m_shader = glCreateShader(GL_VERTEX_SHADER);
    return 1;
}

bool GLShaderFragment::vLoad(const char* f_file)
{
    m_shader = glCreateShader(GL_FRAGMENT_SHADER);
    return 1;
}

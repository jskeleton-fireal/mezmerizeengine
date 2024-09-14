#include "mezstring.h"
#include <string.h>

#define MEZSTRING_DEBUG 0
#if MEZSTRING_DEBUG

#else
#define printf
#endif

char* MezString::cstr()
{
    return m_buffer.m_;
}

const char* MezString::cstr_const()
{
    return m_buffer.m_const;
}

void MezString::newbuffer(int size,bool copy_previous, bool deallocate_previous)
{
    if (size == -1)
    {
        size = strlen(m_buffer.m_) + 1;
    }
        char* oldbuffer = m_buffer.m_;
    m_buffer.m_ = new char[size];
    if (copy_previous)
    {
        memcpy(m_buffer.m_, oldbuffer, size);
    }
    if (deallocate_previous)
    {
        delete[] m_buffer.m_;
    }
    debug_logself(this);
    printf("has a new buffer!\n");

}

void MezString::free()
{
    debug_logself(true);
    printf("is gone!\n");
    delete[] m_buffer.m_;
    m_buffer.m_ = 0;
}
MezString::MezString()
{
    debug_logself(0);
    printf("Called default constructor\n"); 
    m_buffer.m_ = 0;
}
MezString::MezString(const MezString& copy)
{
    debug_logself(0);
    printf("Called copy constructor\n");


    if (!copy.m_buffer.m_) return;
    m_buffer.m_ = copy.m_buffer.m_;
    newbuffer();
}
MezString::MezString(const char* c_str)
{
    set_cstr(c_str);
    debug_logself(1);
    printf("Called CSTR constructor\n");
}
MezString::~MezString()
{
    if (m_buffer.m_) free();
}
void MezString::debug_logself(bool selfisvalid)
{
    if (selfisvalid)
    {
        printf("%x (%s @ %x) ", this, m_buffer.m_, m_buffer.m_);
    }
    else
    {
        printf("%x ( <invalid> )", this);
    }
}
void MezString::set_cstr(const char* cstr)
{
    m_buffer.m_const = cstr;

    newbuffer();
}



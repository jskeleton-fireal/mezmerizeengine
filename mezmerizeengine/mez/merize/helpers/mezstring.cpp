#include "mezstring.h"
#include <string.h>
#include "static_format.h"
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
        delete[] oldbuffer;
    }
    debug_logself(this);
    printf("has a new buffer! (was %x)\n",oldbuffer);

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
        printf("%x (%s @ %x) ", this, m_buffer.m_);
    }
    else
    {
        printf("%x ( ?? )", this);
    }
}
void MezString::set_cstr(const char* cstr)
{
    m_buffer.m_const = cstr;

    newbuffer();
}

void MezString::append(const char* cstr)
{
    int mesize = strlen(m_buffer.m_const);
    int theysize = strlen(cstr);
    int total_size = mesize + theysize;
    char* superbuffer = new char[total_size+1];
    memcpy(superbuffer, m_buffer.m_, mesize);
    memcpy(superbuffer + mesize, cstr, theysize + 1); //copy terminator as well
    set_cstr(superbuffer);
    delete[] superbuffer;
}

MezString MezString::substring(int start)
{
    return mezstring_t(m_buffer.m_ + start);
}

MezString MezString::substring(int start, int end)
{
    assert(end >= start);
    mezstring_t one = substring(start);
    one.m_buffer.m_[(end - start)+1] = '\0';
    return one;
}

MezString MezString::substring_until(const char until_this_char)
{
    for (int i =0;i<strlen(m_buffer.m_const);i++)
    {
        if (m_buffer.m_[i] == until_this_char)
        {
            return substring(0, i-1);
        }
    }
    return "";
}

MezString MezString::substring_until(int start,const char until_this_char)
{
    for (int i = start; i < strlen(m_buffer.m_const); i++)
    {
        if (m_buffer.m_[i] == until_this_char)
        {
            return substring(start, i-1);
        }
    }
    return "";
}

int MezString::length()
{
    return strlen(this->cstr_const());
}





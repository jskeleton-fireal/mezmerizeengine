#include "cmdargs.h"
#include "../merize.h"

bool is_eos(char f_char)
{
    return !f_char || f_char == ' ';
}

ConCommandArgs_Single::ConCommandArgs_Single(const char* f_spot)
{
    m_spot = f_spot;
}

bool ConCommandArgs_Single::Valid()
{
    return m_spot;
}

int ConCommandArgs_Single::Length()
{
    int c = 0;
    while (!is_eos(m_spot[c]))
    {
        c++; //YOOOOO
    }
    return c;
}

void ConCommandArgs_Single::GetString(char* buffer, int buffersize)
{
    int len = Length();
    bool good = buffersize > len;
    assert(good);
    if (!good) return;
    memcpy(buffer, m_spot, len);
    buffer[len] = '\0';
}

int ConCommandArgs_Single::GetInt()
{
    char buffer[64];
    GetString(buffer, 64);
    return atoi(buffer);
}

ConCommandArgs::single_t ConCommandArgs::Get(int argnum)
{
    if (!argnum) return single_t(m_refstr);


        int spot = 0; //our spot in the string
        int counta = 0; //Which arg are we on right now?
        int start = 0; //Where did it start at?
        while (spot < 0x300)
        {
            char c = m_refstr[spot];
            if (c == ' ' || !c)
            {
                bool is_end = !c;
                //!start => never made it past the first arg
                if (is_end && (!start)) 
                { 
                    assert(!(counta > argnum));
                    return single_t(0);
                } 
                if (counta == argnum)
                {
                    single_t single = single_t(&m_refstr[start]);
                    return single;
                }
                counta++;
                start = spot+1;
            }
            spot++;
        }


    assert(0);
    return single_t(0);

}

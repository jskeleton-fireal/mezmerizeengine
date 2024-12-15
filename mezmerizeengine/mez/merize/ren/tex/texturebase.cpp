#include "texturebase.h"
#include "texenums.h"
using namespace tex;
int RTextureBase::get_bpp()
{
    return 32;
}

TextureFormat RTextureBase::get_format()
{
    switch (get_bpp())
    {
    case 32:
        return RGBA8;
    case 24: return RGB8;

    }
    return (TextureFormat)0;
}

void RTextureBase::free()
{
}

 bool RTextureBase::is_point() { return m_flags & point_filter; }

 bool RTextureBase::dont_create_mips() { return (m_flags & no_mips); }

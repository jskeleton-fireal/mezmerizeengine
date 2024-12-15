#include "texloader.h"
#include "texloader_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <mez/merize/deps_headers/stb_image.h>
#include <mez/merize/engine/BaseEngine.h>
#include <mez/merize/helpers/static_format.h>

RTextureBase* RTextureLoader::CreateTextureFromFile(const char* f_filename)
{
    char text[800];
    sprintf_s(text, "content/%s",f_filename);

    int x, y, bpp;

    //not sure what the 1 is for
    byte* raw = stbi_load(text, &x, &y, &bpp, 0);
    const char* failure = stbi_failure_reason();
    if (failure)
    {
        //replace this!!!!
        engine->fatalmsg(static_format("%s FAIL. (%s)\n", f_filename,failure));
    }

    RTexture_TexLoaded* tx = new RTexture_TexLoaded();
    tx->m_data = raw;
    tx->m_bpp = bpp * 8;
    tx->m_Height = y;
    tx->m_Width = x;


    return tx;
}

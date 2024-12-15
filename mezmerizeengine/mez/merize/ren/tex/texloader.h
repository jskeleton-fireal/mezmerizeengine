#pragma once
#include "texture.h"
#include "texturebase.h"
//creates rtextures from files
//uses deps_headers/stb_image.h

class RTextureLoader
{
public:
	static RTextureBase* CreateTextureFromFile(const char* f_filename);
};
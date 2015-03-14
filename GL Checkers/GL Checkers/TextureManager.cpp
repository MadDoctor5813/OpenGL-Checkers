#include <filesystem>
#include <iostream>
#include <SOIL.h>

#include "TextureManager.h"

namespace fs = std::tr2::sys;

TextureManager::TextureManager() {
}


TextureManager::~TextureManager() {
}

GLuint TextureManager::getTexture(const std::string& textureName) {
	return textureMap.at(textureName);
}

void TextureManager::loadTextures() {
	fs::directory_iterator dirIter(imageDir);
	fs::directory_iterator empty;
	for (; dirIter != empty; dirIter++) {
		std::cout << dirIter->path() << std::endl;
		GLuint currentTexture = loadTextureFromFile(dirIter->path());
		textureMap.emplace(dirIter->path().basename(), currentTexture);
	}
}

GLuint TextureManager::loadTextureFromFile(const std::string& filename) {
	GLuint returnTexture;
	returnTexture = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (returnTexture == 0) {
		std::cout << "SOIL Error " << SOIL_last_result() << std::endl;
		return 0;
	}
	else {
		std::cout << "Texture " << filename <<  " loaded";
		return returnTexture;
	}
}

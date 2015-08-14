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
	return textureMap.at(fs::path(textureName).string()); //this should ensure proper backslashing
}

GLuint TextureManager::addTexture(std::string& name, int w, int h, GLubyte* data) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE0, textureId);
	glTexImage2D(GL_TEXTURE0, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE0, 0);
	textureMap.emplace(name, textureId);
	return textureId;
}

void TextureManager::removeTexture(std::string name) { 
	GLuint textureId = textureMap.at(name);
	glDeleteTextures(1, &textureId);
	textureMap.erase(name);
}

void TextureManager::loadTextures() {
	fs::recursive_directory_iterator dirIter(imageDir);
	fs::recursive_directory_iterator empty;
	for (; dirIter != empty; dirIter++) {
		if (dirIter->path().extension() == ".png") {
			std::string path = dirIter->path().string();
			std::string texName = path.substr(path.find_first_of("/\\") + 1, path.length() - 1); //this strips the first part of the path off
			textureMap.emplace(fs::path(texName).replace_extension("").string(), loadTextureFromFile(path));
		}
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
		std::cout << "Texture " << filename << " loaded" << std::endl;
		return returnTexture;
	}
}

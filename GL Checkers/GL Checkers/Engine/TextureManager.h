#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>

class TextureManager {

public:
	TextureManager();
	~TextureManager();

	GLuint getTexture(const std::string& imageName);
	GLuint addTexture(std::string& name, int w, int h, GLubyte* data);
	void pruneEmptyTextures();
	void loadTextures();

private:
	GLuint loadTextureFromFile(const std::string& filename);

	std::string imageDir = "Images/";
	std::unordered_map<std::string, GLuint> textureMap;

};


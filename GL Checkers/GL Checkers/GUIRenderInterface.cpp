#include "GUIRenderInterface.h"

#include <GL\glew.h>

GUIRenderInterface::GUIRenderInterface(App& app) : appRef(app) {
}


GUIRenderInterface::~GUIRenderInterface() {
}

void GUIRenderInterface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation) {

}

Rocket::Core::CompiledGeometryHandle GUIRenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture) {
	return 0;
}

void GUIRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation) {

}

void GUIRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry) {

}

bool GUIRenderInterface::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source) {
	GLuint textureId = appRef.getTextureManager().getTexture(source.CString());
	if (textureId == 0) {
		//invalid texture
		return false;
	}
	else {
		texture_handle = textureId;
		int w, h;
		glBindTexture(GL_TEXTURE0, textureId);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h); //this is a hacky way to get a texture's size, but rewriting the texture manager to handle it seems like too much work for now
		glBindTexture(GL_TEXTURE0, 0);
		texture_dimensions.x = w;
		texture_dimensions.y = h;
	}
	return true;
}

bool GUIRenderInterface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions) {
	const int len = 16;
	char s[len];
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)]; //gemerates a random string to use as the name for the generated textures
	}
	s[len] = 0;
	int textureId = appRef.getTextureManager().addTexture(std::string("Rocket_generated").append(s), source_dimensions.x, source_dimensions.y, (GLubyte*)source);
	texture_handle = textureId;
	return true; //no error checking for now
}

void GUIRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle) {
	glDeleteTextures(1, &texture_handle);
	appRef.getTextureManager().pruneEmptyTextures();
}

void GUIRenderInterface::EnableScissorRegion(bool enable) {
	if (enable) {
		glEnable(GL_SCISSOR_TEST);
	}
	else {
		glDisable(GL_SCISSOR_TEST);
	}
}

void GUIRenderInterface::SetScissorRegion(int x, int y, int width, int height) {
	glScissor(x, appRef.screenHeight - (y + height), width, height);
}
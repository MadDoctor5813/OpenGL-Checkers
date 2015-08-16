#pragma once

#include <Rocket/Core/Core.h>

class App;

class GUIRenderInterface : public Rocket::Core::RenderInterface {

public:
	GUIRenderInterface(App& app);
	~GUIRenderInterface();

	virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
	//Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
	//void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
	//void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

	virtual void EnableScissorRegion(bool enable);
	virtual void SetScissorRegion(int x, int y, int width, int height);

	virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
	virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
	virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

private:
	App& appRef;

};


#pragma once

#include <Rocket/Core.h>

#include "Engine\DrawBatch.h"

class GUIRenderHelper {

public:
	GUIRenderHelper();
	~GUIRenderHelper();
	
	static DrawBatch toBatch(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);

};


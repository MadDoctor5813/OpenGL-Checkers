#pragma once

#include <gl\glew.h>
#include "Engine\IndexedRenderer.h"

class SpriteRenderHelper {
public:
	static DrawBatch toBatch(float x, float y, float w, float h);
};


#pragma once

#include <gl\glew.h>
#include "Engine\IndexedRenderer.h"

class SpriteRenderHelper {
public:
	static DrawBatch toBatch(int x, int y, int w, int h);
};


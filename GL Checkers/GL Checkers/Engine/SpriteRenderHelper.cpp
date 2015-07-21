#include "SpriteRenderHelper.h"

DrawBatch SpriteRenderHelper::toBatch(int x, int y, int w, int h, GLuint texture) {
	Vertex v1, v2, v3, v4;
	v1.color = { 255, 255, 255, 255 };
	v1.pos = { x, y };
	v1.texCoord = { 0.0f, 0.0f };
	v2.color = { 255, 255, 255, 255 };
	v2.pos = { x, y + h };
	v2.texCoord = { 0.0f, 1.0f };
	v3.color = { 255, 255, 255, 255 };
	v3.pos = { x + w, y + h };
	v3.texCoord = { 1.0f, 1.0f };
	v4.color = { 255, 255, 255, 255 };
	v4.pos = { x + w, y };
	v4.texCoord = { 1.0f, 0.0f };
	return DrawBatch{ { v1, v2, v3, v4 }, { 0, 1, 2, 0, 2, 3 }, { texture } };
}
#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Vertex.h"
#include "Sprite.h"

struct Glyph {
	GLuint texture;
	int depth;
	Vertex topLeft;
	Vertex topRight;
	Vertex bottomLeft;
	Vertex bottomRight;
};

struct Batch {
	int vboOffset;
	int vertexes;
	GLuint texture;
	Batch(int offset, int vertexes, GLuint texture) : vboOffset(offset), vertexes(vertexes), texture(texture) {}
};

enum class SortMethods {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE_SORT
};

class SpriteBatch {

public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(SortMethods method = SortMethods::TEXTURE_SORT);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4& uv, GLuint texture, int depth, const Color& color);
	void render();

private:
	GLuint vboId = 0;
	GLuint vaoId = 0;
	SortMethods sortMethod;

	std::vector<Glyph *> glyphs;
	std::vector<Batch> batches;


	void makeBatches();
	void sortGlyphs();
	void makeVAO();
	void renderBatch(const Batch& batch);

	static bool sortTexture(Glyph * a, Glyph * b);
	static bool sortFrontToBack(Glyph * a, Glyph * b);
	static bool sortBackToFront(Glyph * a, Glyph * b);

};


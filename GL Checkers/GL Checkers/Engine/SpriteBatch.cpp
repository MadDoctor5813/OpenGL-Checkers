#include "SpriteBatch.h"

#include <algorithm>




SpriteBatch::SpriteBatch() {

}


SpriteBatch::~SpriteBatch() {

}

void SpriteBatch::init() {
	makeVAO();
}

void SpriteBatch::makeVAO() {
	if (vaoId == 0) {
		glGenVertexArrays(1, &vaoId);
	}
	glBindVertexArray(vaoId);
	if (vboId == 0) {
		glGenBuffers(1, &vboId);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//Enable arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//Set position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	//Set texture coord attrib pointer
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	//Set color attrib pointer
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//Unbind array
	glBindVertexArray(0);
}

void SpriteBatch::makeBatches() {
	if (glyphs.empty()) {
		return;
	}
	std::vector<Vertex> vertices;
	vertices.resize(glyphs.size() * 6);

	int curVertex = 0;
	int offset = 0;
	batches.emplace_back(offset, 6, glyphs[0]->texture); //Init first 6 vertices in first batch
	vertices[curVertex++] = glyphs[0]->topLeft;
	vertices[curVertex++] = glyphs[0]->bottomLeft;
	vertices[curVertex++] = glyphs[0]->bottomRight;
	vertices[curVertex++] = glyphs[0]->bottomRight;
	vertices[curVertex++] = glyphs[0]->topRight;
	vertices[curVertex++] = glyphs[0]->topLeft;
	offset += 6;

	for (int curGlyph = 1; curGlyph < glyphs.size(); curGlyph++) {
		if (glyphs[curGlyph]->texture != glyphs[curGlyph - 1]->texture) { //if the texture has changed make a new batch
			batches.emplace_back(offset, 6, glyphs[curGlyph]->texture);
		}
		else {
			batches.back().vertexes += 6; //otherwise add 6 more vertices to the last batch
		}
		vertices[curVertex++] = glyphs[curGlyph]->topLeft;
		vertices[curVertex++] = glyphs[curGlyph]->bottomLeft;
		vertices[curVertex++] = glyphs[curGlyph]->bottomRight;
		vertices[curVertex++] = glyphs[curGlyph]->bottomRight;
		vertices[curVertex++] = glyphs[curGlyph]->topRight;
		vertices[curVertex++] = glyphs[curGlyph]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboId); 
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); //quickly clear data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()); //upload data
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

void SpriteBatch::begin(SortMethods method /* = SortMethods::TEXTURE_SORT */) {
	sortMethod = method;
	glyphs.clear();
	batches.clear();

}

void SpriteBatch::draw(const glm::vec4& dest, const glm::vec4& uv, GLuint texture, int depth, const Color& color) {
	Glyph * newGlyph = new Glyph();
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.pos = { dest.x, dest.y + dest.w }; //W means height. Blame GLM for not providing aliases
	newGlyph->topLeft.texCoord = { uv.x, uv.y + uv.w };

	newGlyph->topRight.color = color;
	newGlyph->topRight.pos = { dest.x + dest.z, dest.y + dest.w }; //Same here. Z actually means width
	newGlyph->topRight.texCoord = { uv.x + uv.z, uv.y + uv.w };

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.pos = { dest.x, dest.y };
	newGlyph->bottomLeft.texCoord = { uv.x, uv.y };

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.pos = { dest.x + dest.z, dest.y };
	newGlyph->bottomRight.texCoord = { uv.x + uv.z, uv.y };

	glyphs.push_back(newGlyph);
}

void SpriteBatch::end() {
	sortGlyphs();
	makeBatches();
}

void SpriteBatch::sortGlyphs() {
	switch (sortMethod) {
	case SortMethods::FRONT_TO_BACK:
		std::stable_sort(glyphs.begin(), glyphs.end(), sortTexture);
		break;
	case SortMethods::BACK_TO_FRONT:
		std::stable_sort(glyphs.begin(), glyphs.end(), sortBackToFront);
		break;
	case SortMethods::TEXTURE_SORT:
		std::stable_sort(glyphs.begin(), glyphs.end(), sortFrontToBack);
		break;
	}
}

bool SpriteBatch::sortTexture(Glyph * a, Glyph * b) {
	return (a->texture < b->texture);
}

bool SpriteBatch::sortFrontToBack(Glyph * a, Glyph * b) {
	return (a->depth < b->depth);
}

bool SpriteBatch::sortBackToFront(Glyph * a, Glyph * b) {
	return (a->depth > b->depth);
}

void SpriteBatch::render() {

	for (auto batch : batches) {
		renderBatch(batch);
	}
}

void SpriteBatch::renderBatch(const Batch& batch) {
	glBindVertexArray(vaoId);
	glBindTexture(GL_TEXTURE_2D, batch.texture);
	glDrawArrays(GL_TRIANGLES, batch.vboOffset, batch.vertexes);
}

#include "GUIRenderHelper.h"

#include <glm/common.hpp>

GUIRenderHelper::GUIRenderHelper() {
}


GUIRenderHelper::~GUIRenderHelper() {
}

DrawBatch GUIRenderHelper::toBatch(Rocket::Core::Vertex * vertices, int num_vertices, int * indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f & translation) {
	//Convert from libRocket's vertex format to ours
	std::vector<Vertex> vertVec;
	for (int i = 0; i < num_vertices; i++) {
		Rocket::Core::Vertex current = vertices[i];
		Vertex newVertex;
		newVertex.pos = { current.position.x + translation.x, current.position.y + translation.y };
		newVertex.color = { current.colour.red, current.colour.blue, current.colour.green, current.colour.alpha };
		newVertex.texCoord = { current.tex_coord.x, current.tex_coord.y };
		vertVec.push_back(newVertex);
	}
	//Copy indexes into a vector
	std::vector<GLuint> indexVec;
	for (int i = 0; i < num_indices; i++) {
		int index = indices[i];
		indexVec.push_back((GLuint)index);
	}
	return DrawBatch{ vertVec, indexVec, (GLuint)texture };
}

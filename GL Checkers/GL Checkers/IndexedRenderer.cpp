#include "IndexedRenderer.h"


IndexedRenderer::IndexedRenderer() {

}


IndexedRenderer::~IndexedRenderer() {

}

void IndexedRenderer::initGLObjects() {
	//generate the needed GL objects
	glGenBuffers(1, &vboId);
	glGenBuffers(1, &elementBufferId); 
	glGenVertexArrays(1, &vaoId);
	//create VAO state
	glBindVertexArray(vaoId);
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
	//Cleanup
	glBindVertexArray(0);
}

void IndexedRenderer::draw(std::vector<Vertex>& vertexes, std::vector<int>& indexes, GLuint texture) {
	//if the texture isn't already being batched, make a new batch
	if (batches.count(texture) == 0) {
		batches.emplace(texture, DrawBatch());
	} 
	DrawBatch batch = batches.at(texture);
	//add vertices for this call to the batch
	batch.vertexes.insert(batch.vertexes.end(), vertexes.begin(), vertexes.end());
	//modify indexes to point to proper locations after the append
	for (int& index : indexes) {
		index += batch.indexes.size();
	}
	//append indexes
	batch.indexes.insert(batch.indexes.end(), indexes.begin(), indexes.end());
}

void IndexedRenderer::render() {
	//compile data
	compileVbo();
	compileElementBuffer();
	//bind buffers and vertex array
	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	//put data into buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * compiledVbo.size(), compiledVbo.data(), GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * compiledElementBuffer.size(), compiledElementBuffer.data(), GL_STREAM_DRAW);
	//make draw calls
	int offset;
	for (auto entry : batches) {
		glDrawElementsBaseVertex(GL_TRIANGLES, entry.second.indexes.size(), GL_UNSIGNED_INT, (void*)&entry.second.indexes[offset], offset);
		offset += entry.second.indexes.size();
	}
}

void IndexedRenderer::compileVbo() {
	compiledVbo.clear();
	for (auto entry : batches) {
		//add vertexes to total vbo
		compiledVbo.insert(compiledVbo.end(), entry.second.vertexes.begin(), entry.second.vertexes.end());
	}
}

void IndexedRenderer::compileElementBuffer() {
	compiledElementBuffer.clear();
	for (auto entry : batches) {
		//append the indexes
		compiledElementBuffer.insert(compiledElementBuffer.end(), entry.second.indexes.begin(), entry.second.indexes.end());
	}
}

#include "Sprite.h"
#include "Vertex.h"
#include "Game.h"

#include <vector>


Sprite::Sprite(float x, float y, float w, float h, Game& game) : x(x), y(y), w(w), h(h), bufferId(0), gameRef(game) {
	initBuffer();
	texId = gameRef.getTextureManager().getTexture("taco");
}


Sprite::~Sprite() {
	if (bufferId != 0) {
		glDeleteBuffers(1, &bufferId);
	}
}


void Sprite::initBuffer() {
	//Create vertex buffer
	if (bufferId == 0) {
		glGenBuffers(1, &bufferId);
	}

	//Create vertex data to place in buffer. VertData is arranged x coord , then y coord in CCW order. Origin of sprite is bottom left
	std::vector<Vertex> vertData(6);
	//First triangle in quad
	//Vertex 1, top right
	vertData[0].pos.x = x + w;
	vertData[0].pos.y = y + h;
	vertData[0].texCoord = { 1.0f, 1.0f };
	vertData[0].color = { 255, 255, 255, 255 };
	//Vertex 2, top left
	vertData[1].pos.x = x;
	vertData[1].pos.y = y + h;
	vertData[1].texCoord = { 0.0f, 1.0f };
	vertData[1].color = { 255, 255, 255, 255 };
	//Vertex 3, bottom left
	vertData[2].pos.x = x;
	vertData[2].pos.y = y;
	vertData[2].texCoord = { 0.0f, 0.0f };
	vertData[2].color = { 255, 255, 255, 255 };
	//Second triangle in quad
	//Vertex 1, bottom left (repeated)
	vertData[3].pos.x = x;
	vertData[3].pos.y = y;
	vertData[3].texCoord = { 0.0f, 0.0f };
	vertData[3].color = { 255, 255, 255, 255 };
	//Vertex 2, bottom right
	vertData[4].pos.x = x + w;
	vertData[4].pos.y = y;
	vertData[4].texCoord = { 1.0f, 0.0f };
	vertData[4].color = { 255, 255, 255, 255 };
	//Vertex 3, top right (repeated)
	vertData[5].pos.x = x + w;
	vertData[5].pos.y = y + h;
	vertData[5].texCoord = { 1.0f, 1.0f };
	vertData[5].color = { 255, 255, 255, 255 };

	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	//Copy vertData to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertData.size(), vertData.data(), GL_STATIC_DRAW);

	//Unbind buffer for cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	//Set position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	//Set texture coord attrib pointer
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	//Set color attrib pointer
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//Set texture
	glBindTexture(GL_TEXTURE_2D, texId);
	glActiveTexture(GL_TEXTURE0);
	GLint textureLoc = glGetUniformLocation(gameRef.getCurrentProgram(), "spriteTexture");
	glUniform1i(textureLoc, 0);
	//Set camera transform
	GLint transformLoc = glGetUniformLocation(gameRef.getCurrentProgram(), "camTransform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &(gameRef.getCamera().getMatrix()[0][0]));
	//Draw buffer
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//Unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

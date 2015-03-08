#include "Sprite.h"
#include "Vertex.h"

#include <vector>


Sprite::Sprite(float x, float y, float w, float h) : x(x), y(y), w(w), h(h), bufferId(0) {
	initBuffer();
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
	vertData[0].color = { 255, 0, 0, 255 };
	//Vertex 2, top left
	vertData[1].pos.x = x;
	vertData[1].pos.y = y + h;
	vertData[1].color = { 0, 255, 0, 255 };
	//Vertex 3, bottom left
	vertData[2].pos.x = x;
	vertData[2].pos.y = y;
	vertData[2].color = { 0, 0, 255, 255 };
	//Second triangle in quad
	//Vertex 1, bottom left (repeated)
	vertData[3].pos.x = x;
	vertData[3].pos.y = y;
	vertData[3].color = { 0, 0, 255, 255 };
	//Vertex 2, bottom right
	vertData[4].pos.x = x + w;
	vertData[4].pos.y = y;
	vertData[4].color = { 255, 255, 0, 255 };
	//Vertex 3, top right (repeated)
	vertData[5].pos.x = x + w;
	vertData[5].pos.y = y + h;
	vertData[5].color = { 255, 0, 0, 255 };

	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	//Copy vertData to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), &vertData[0], GL_STATIC_DRAW);
	//Unbind buffer for cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	//Enables first attrib array
	glEnableVertexAttribArray(0);
	//Enables second attrib array
	glEnableVertexAttribArray(1);
	//Set position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
	//Set color attrib pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
	//Draw arrays
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//Disable first attrib array
	glDisableVertexAttribArray(0);
	//Disable second attrib array
	glDisableVertexAttribArray(1);
	//Unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

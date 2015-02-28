#include "Sprite.h"


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
	float vertData[12];
	//First triangle in quad
	//Vertex 1, top right
	vertData[0] = x + w;
	vertData[1] = y + h;
	//Vertex 2, top left
	vertData[2] = x;
	vertData[3] = y + h;
	//Vertex 3, bottom left
	vertData[4] = x;
	vertData[5] = y;
	//Second triangle in quad
	//Vertex 1, bottom left (repeated)
	vertData[6] = x;
	vertData[7] = y;
	//Vertex 2, bottom right
	vertData[8] = x + w;
	vertData[9] = y;
	//Vertex 3, top right (repeated)
	vertData[10] = x + w;
	vertData[11] = y + h;

	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	//Copy vertData to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);
	//Unbind buffer for cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	//Enables first attrib array
	glEnableVertexAttribArray(0);
	//Sets buffer data attributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//Draws buffer
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//Disable attrib array
	glDisableVertexAttribArray(0);
	//Unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

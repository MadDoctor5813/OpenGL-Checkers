#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {

public:
	Camera2D();
	~Camera2D();

	void init(float screenWidth, float screenHeight);
	void update();

	void setPos(const glm::vec2& pos);
	void setScale(float scale);

	void translate(const glm::vec2& translation);
	void zoom(float zoom);

	glm::vec2 getPos() { return camPos; }
	float getScale() { return camScale; }
	glm::mat4 getMatrix() { return camMatrix; }

private:

	float camScale = 1.0f;
	bool updateNeeded = true;

	float width;
	float height;

	glm::vec2 camPos;
	glm::mat4 camMatrix;

};


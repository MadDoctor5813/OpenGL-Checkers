#version 130

in vec2 vertPos; //Vertex's 2D position
in vec2 vertTexPos; //Texture coord
in vec4 vertColor; //color in RGBA format

out vec2 fragTexPos;
out vec4 fragColor;

uniform mat4 camTransform;

void main() {
	//Set position, z is zero because of 2d, and w is 1 because of magic opengl stuff or something
	gl_Position.xy = (camTransform * vec4(vertPos.x, vertPos.y, 0.0f, 1.0f)).xy;
	gl_Position.z = 0.0f;
	gl_Position.w = 1.0f;
	//Send values through to fragment shader
	fragTexPos = vertTexPos;
	fragColor = vertColor;
}
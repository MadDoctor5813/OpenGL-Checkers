#version 130

in vec2 vertPos;
in vec4 vertColor;

out vec4 fragColor;

void main() {
	//Set position
	gl_Position.xy = vertPos;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	//Forward color to fragment shader
	fragColor = vertColor;
}
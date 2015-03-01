#version 130

in vec2 vertPos;

void main() {

	gl_position.xy = vertPos;

}
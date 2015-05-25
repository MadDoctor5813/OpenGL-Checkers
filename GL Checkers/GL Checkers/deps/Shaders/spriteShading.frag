#version 130

in vec2 fragTexPos;
in vec4 fragColor;

uniform sampler2D spriteTexture;

out vec4 outColor;

void main() {
	//Set color, by multiplying texture color and vertex color
	outColor = texture(spriteTexture, vec2(fragTexPos.x, 1.0 - fragTexPos.y)) * fragColor;
}
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_diffuse1;

void main() {
	FragColor = vec4(0.0, 0.0, 0.0, 0.0);
}

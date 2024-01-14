#version 330

out vec4 FragColor;

uniform vec3 uColor;              // Color

void main() {
	FragColor = vec4(uColor, 1.0);
}

#version 330

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTex;           // Texture
uniform vec3 uColor;              // Color

void main() {
  vec4 texColor = texture(uTex, TexCoord);
	FragColor = texColor * vec4(uColor, 1.0);
}

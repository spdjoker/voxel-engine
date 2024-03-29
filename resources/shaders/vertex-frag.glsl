#version 330

out vec4 FragColor;

in vec2 TexCoord;
in vec3 vertexColor;

uniform sampler2D uTex;           // Texture

void main() {
  vec4 texColor = texture(uTex, TexCoord);
	FragColor = texColor * vec4(vertexColor, 1.0);
}

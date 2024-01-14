#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texUV;

uniform mat4 uModelMatrix;
uniform mat4 uCameraMatrix;

out vec2 TexCoord;

void main() {
	gl_Position = uCameraMatrix * uModelMatrix * vec4(aPos, 1.0);
  TexCoord = texUV;
}

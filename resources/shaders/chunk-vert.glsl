#version 330

layout (location = 0) in vec3 aPos;

out float i;

uniform mat4 uCameraMatrix;
uniform mat4 uModelMatrix;

void main() {
	gl_Position = uCameraMatrix * uModelMatrix * vec4(aPos, 1.0);
  i = aPos.x;
}

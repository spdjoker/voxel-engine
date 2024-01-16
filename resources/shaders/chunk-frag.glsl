#version 330

out vec4 FragColor;

in float i;

uniform vec3 uColor;              // Color

void main() {
  vec3 colors[4] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0),
    vec3(1.0, 1.0, 1.0)
  );

  FragColor = vec4(colors[int(floor(4 * (i + 0.5)))], 1.0);
}

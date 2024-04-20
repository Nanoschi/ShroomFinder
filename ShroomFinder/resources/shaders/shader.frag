#version 460 core

out vec4 fragColor;

in vec2 v_pos;

void main() {
	fragColor = vec4(0.0, distance(v_pos, vec2(0, 0)) < 0.5, 0.0, 1.0);
}
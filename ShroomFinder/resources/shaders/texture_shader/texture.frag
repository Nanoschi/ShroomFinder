#version 460 core

out vec4 fragColor;

in vec2 v_pos;
in vec2 v_uv;

uniform sampler2D tex;

void main() {
	fragColor = texture(tex, v_uv);
}
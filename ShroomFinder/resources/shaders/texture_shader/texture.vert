#version 460 core

layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec2 a_uv;

uniform vec2 u_scale;
uniform vec2 u_position;
uniform vec2 u_zoom;

out vec2 v_pos;
out vec2 v_uv;

void main() {
	vec2 scaled_pos = a_pos * u_scale;
	vec2 moved_pos = scaled_pos + u_position;
	vec2 zoomed_pos = moved_pos * u_zoom;

	gl_Position = vec4(zoomed_pos, 1.0, 1.0);
	v_pos = a_pos;
	v_uv = a_uv;
}
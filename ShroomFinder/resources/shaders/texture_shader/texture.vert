#version 460 core

layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec2 a_uv;

uniform vec2 u_scale;
uniform vec2 u_position;

out vec2 v_pos;
out vec2 v_uv;

void main() {	
	vec2 moved_pos = a_pos + u_position;
	vec2 scaled_pos = moved_pos * u_scale;

	gl_Position = vec4(scaled_pos, 0.0, 1.0);
	v_pos = a_pos;
	v_uv = a_uv;
}
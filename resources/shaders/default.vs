#version 330 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 texcoords;

uniform vec2 position;
uniform float window_ratio;

out vec2 uv;

void main() {
    vec2 final_pos = vertex_position+position;
    if(window_ratio >= 1.0)
        final_pos.x /= window_ratio;
    else
        final_pos.y *= window_ratio;
    gl_Position = vec4(final_pos, 0.0, 1.0);
    uv = texcoords;
}

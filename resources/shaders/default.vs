#version 330 core

layout(location = 0) in vec2 vertex_position;

uniform vec2 position;
uniform float window_ratio;

void main() {
    vec2 final_pos = vertex_position+position;
    final_pos.y *= window_ratio;
    gl_Position = vec4(final_pos, 0.0, 1.0);
}

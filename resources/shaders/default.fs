#version 330 core

uniform vec3 color;
uniform int use_texture;
uniform sampler2D sampler;
in vec2 uv;
out vec4 out_color;

void main() {
    if(use_texture != 0)
        out_color = texture(sampler, uv);
    else
        out_color = vec4(color, 1.0);
}


// basic exemple of fragment shader (GLSL)

// fragment shader program

#version 450

layout(location = 0) in  vec4 in_color;
layout(location = 1) out vec4 out_color;

void main() {
	out_color = in_color;
}


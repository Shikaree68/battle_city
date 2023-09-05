#version 460
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 texture_coords;
out vec3 color;
out vec2 tex_coords;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

void main() 
{
   color = vertex_color;
   tex_coords = texture_coords;
   gl_Position = projection_matrix * model_matrix * vec4(vertex_position, 1.0);
}
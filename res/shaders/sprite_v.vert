#version 460
layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 texture_coords;
out vec2 tex_coords;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform float layer;

void main() 
{
   tex_coords = texture_coords;
   gl_Position = projection_matrix * model_matrix * vec4(vertex_position, layer, 1.0);
}
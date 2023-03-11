#version 330

// Input
// TODO(student): Get vertex attributes from each location
// layout(location = 0) in vec3 v_position;
// layout(location = 1) in vec3 v_normal;
// layout(location = 2) in vec2 v_coord;
// layout(location = 3) in vec3 v_color;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_coord;
layout(location = 3) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection; 
uniform float Time; 
uniform vec3 car_position;
uniform float scale_factor;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_coord;
out vec3 frag_color;

void main()
{
    vec3 vertex_position = vec3(Model * vec4(v_position, 1.0));
    vertex_position.y = vertex_position.y - pow(distance(car_position, vertex_position), 2) * scale_factor;
    
    frag_position = vertex_position;
    frag_normal = v_normal;
    frag_coord = v_coord;
    frag_color = v_color * Time;

     gl_Position = Projection * View * vec4(vertex_position, 1.0);
}

#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform int yes_earth;
uniform float time;
uniform int yes_grass;

// Output
out vec2 texcoord;


void main()
{
    // TODO(student): Pass v_texture_coord as output to fragment shader
    vec2 texture_coord = v_texture_coord;

    if (yes_earth == 1) {
        texture_coord.x += time * 0.15f;
    }

    gl_Position = Projection * View * Model * vec4(v_position, 1.0);

     /*
     if (yes_grass == 1) {
         texture_coord.y += gl_Position.y;
    }
    */

    texcoord = texture_coord;
}

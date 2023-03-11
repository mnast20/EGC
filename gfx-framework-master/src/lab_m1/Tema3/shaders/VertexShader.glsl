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
uniform int yes_right;
uniform float time;
uniform float angle_rotate;
uniform vec3 position_player;

// Output
out vec2 texcoord;
out vec3 world_position;
out vec3 world_normal;


void main()
{
    // TODO(student): Pass v_texture_coord as output to fragment shader
    vec2 texture_coord = v_texture_coord;
    world_position = vec3 (Model * vec4(v_position, 1));
    world_normal = normalize (vec3 (Model * vec4(v_normal, 0)));

    float dist = distance(position_player, world_position);

    if (yes_earth == 1) {
        texture_coord.x += time * 0.0005f * position_player.x;
        texture_coord.y -= time * 0.0008f * position_player.z;
    }

    gl_Position = Projection * View * Model * vec4(v_position, 1.0);

    texcoord = texture_coord;
}

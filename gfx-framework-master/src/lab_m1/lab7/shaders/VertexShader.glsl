#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;


void main()
{
    // TODO(student): Compute world space vectors
    vec3 world_position = vec3 (Model * vec4(v_position, 1));
    vec3 world_normal = normalize (vec3 (Model * vec4(v_normal, 0)));

    vec3 L = normalize (light_position - world_position);
    vec3 V = normalize (eye_position - world_position);
    vec3 R = reflect (-L, world_normal);
    vec3 H = normalize( L + V );

    float globalAmbientalColor =  0.25f;
    float dist = distance(light_position, world_position);
    float constant_att_fact = 0.25f;
    float liniar_att_fact = 0.5f;
    float square_att_fact = 0.75f;

    float attenuation_factor = 1 / (constant_att_fact + dist * liniar_att_fact + dist * dist * square_att_fact);

    float emissive_light = 0;

    // TODO(student): Define ambient light component
    float ambient_light = material_kd * globalAmbientalColor;

    // TODO(student): Compute diffuse light component
    float diffuse_light = material_kd * max (dot(world_normal, L), 0);

    // TODO(student): Compute specular light component
    float specular_light = 0;

    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Gouraud (1971) shading method. There is also the Phong (1975) shading
    // method, which we'll use in the future. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
        specular_light = material_ks * pow(max (dot(world_normal, H), 0), material_shininess);
    }

    // TODO(student): Compute light
    // vec3 light_color = vec3(ambient_light, diffuse_light, specular_light);
    float light_color = ambient_light + (diffuse_light + specular_light) * attenuation_factor;

    // TODO(student): Send color light output to fragment shader
    // color = vec3(light_color);
    color = light_color * object_color;

    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}

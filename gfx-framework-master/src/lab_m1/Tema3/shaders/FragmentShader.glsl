#version 330

// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

struct punctiformObject {
    vec3 coordinates;
    vec3 color;
};

uniform vec3 directional_light_position;
uniform vec3 directional_light_direction;
uniform vec3 spotlight_position[201];
uniform vec3 spotlight_direction;
uniform punctiformObject punctiforms[201];
uniform vec3 punctiform_direction;

uniform int nr_spotlight;
uniform int nr_punctiform;

uniform float cut_off;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
// TODO(student): Declare various other uniforms

// Output
layout(location = 0) out vec4 out_color;

float point_light_contribution(vec3 light_position, vec3 light_direction, vec3 world_position, vec3 world_normal, vec3 eye_position, vec3 object_color, int yes_spotlight, int yes_direction) {
    float ambient_light = 0.25;
    float diffuse_light = 0;
    float specular_light = 0;

    world_normal = normalize(world_normal);

    vec3 L = normalize (light_position);
    if (yes_direction == 0) {
        vec3 L = normalize (light_position - world_position);
    }
    vec3 V = normalize (eye_position - world_position);
    vec3 R = reflect (-L, world_normal);
    vec3 H = normalize( L + V );

    float globalAmbientalColor =  0.25f;
    float dist = distance(light_position, world_position);
    float constant_att_fact = 200;
    float liniar_att_fact = 0.5f;
    float square_att_fact = 4.0f;

    float attenuation_factor = 1;

    if (yes_direction == 0) {
        attenuation_factor = 1 / (constant_att_fact + dist * liniar_att_fact + dist * dist * square_att_fact);
    }

    float emissive_light = 0;

    // TODO(student): Compute diffuse light component
    diffuse_light = material_kd * max (dot(world_normal, L), 0);

    // TODO(student): Compute specular light component
    specular_light = 0;

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

    float light = 0;

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    if (yes_spotlight == 1) {
        float spot_light = dot(-L, normalize(light_direction));
        float spot_light_limit = cos(radians(cut_off));

        if (spot_light > spot_light_limit) {
	        // Quadratic attenuation
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            attenuation_factor *= pow(linear_att, 2);
        } else {
            attenuation_factor = 0;
        }
    } 

    light = (diffuse_light + specular_light) * attenuation_factor;
    return light;
}

void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    vec4 color1 = texture2D(texture_1, texcoord);
    vec4 color2 = texture2D(texture_2, texcoord);

    if (color1.a <= 0.1f) {
        discard;
    }

    if (color2.a <= 0.1f) {
        discard;
    }

    vec4 color = mix(color1, color2, 0.5f);

    if (color.a <= 0.1f) {
        discard;
    }

    vec3 object_color = color.xyz;

    vec3 light = vec3(0);

    vec3 color_light1 = vec3(70, 130, 180) / 255.0f;
    light += 0.2f * point_light_contribution(directional_light_position, directional_light_direction, world_position, world_normal, eye_position, object_color, 0, 1) * color_light1 * 5;

    vec3 color_light2 = vec3(0, 255, 0) / 255.0f;
    vec3 color_light3 = vec3(255, 0, 0) / 255.0f;

    for (int i = 0; i < nr_punctiform; i++) {
        if (punctiforms[i].coordinates != vec3(0, 0, 0)) {
            if (punctiforms[i].color != vec3(1, 0, 0)) {
                light += point_light_contribution(punctiforms[i].coordinates, punctiform_direction, world_position, world_normal, eye_position, object_color, 0, 0) * punctiforms[i].color * 300;
            } else {
                light += point_light_contribution(punctiforms[i].coordinates, punctiform_direction, world_position, world_normal, eye_position, object_color, 0, 0) * punctiforms[i].color * 70;
            }
        }
    }
    
    vec3 color_light4 = vec3(255, 250, 205) / 255.0f;
    for (int i = 0; i < nr_spotlight; i++) {
        if (spotlight_position[i] != vec3(0, 0, 0)) {
            vec3 direction = vec3(0, -1, 0);
            light += point_light_contribution(spotlight_position[i], direction, world_position, world_normal, eye_position, object_color, 0, 0) * color_light4 * 250;
        }
    }
    
    float globalAmbientalColor = 1.3f;
    float ambient_color = material_kd * globalAmbientalColor;

    light += ambient_color;
    out_color = vec4(light.x * object_color.x, light.y * object_color.y, light.z * object_color.z, 1);
}

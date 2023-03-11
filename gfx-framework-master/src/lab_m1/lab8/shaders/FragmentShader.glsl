#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction[2];
uniform vec3 light_position[2];
uniform float cut_off;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
uniform int spot_light_yes;

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

float point_light_contribution(vec3 light_position, vec3 light_direction, vec3 world_position, vec3 world_normal, vec3 eye_position, vec3 object_color) {
    float ambient_light = 0.25;
    float diffuse_light = 0;
    float specular_light = 0;

    world_normal = normalize(world_normal);

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
    // ambient_light = material_kd * globalAmbientalColor;
    ambient_light = 1 * 1;

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

    float light_color;

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    if (spot_light_yes == 1) {
        float spot_light = dot(-L, normalize(light_direction));
        float spot_light_limit = cos(radians(cut_off));

        if (spot_light > spot_light_limit) {
	        // Quadratic attenuation
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            attenuation_factor *= pow(linear_att, 2);

            // light_color = attenuation_factor;
        } else {
            attenuation_factor = 0;
        }
    } 

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    light_color = (diffuse_light + specular_light) * attenuation_factor;
    

    return light_color;
}


void main()
{
        float light_color = 0;
        // TODO(student): Write pixel out color
        for (int i = 0; i < 2; i++) {
            light_color += point_light_contribution(light_position[i], light_direction[i], world_position, world_normal, eye_position, object_color);
        }

        float globalAmbientalColor = 0.25f;
        float ambient_color = material_kd * globalAmbientalColor;
        // float ambient_color = 1 * 1;
        light_color += ambient_color;
        out_color = vec4(light_color * object_color, 1);
}

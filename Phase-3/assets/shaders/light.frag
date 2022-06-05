#version 330

/* ===== ----- ===== TODO_LIGHT  ===== ----- ===== */
#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2
#define MAX_LIGHTS 8

/*TODO_LIGHT*///Remove the ambient component from the light struct and add it only before entering the loop (remove from loop)
struct Light {
    int type;
    vec3 direction;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 attenuation;
    vec3 position;
    vec2 cone_angles;
};
uniform Light lights[MAX_LIGHTS];
uniform int light_count;

/*TODO_LIGHT*/// Make for it a sky light struct (to be received form main)
struct Sky {
    vec3 top, middle, bottom;
};
uniform Sky sky;

/*
    Material struct include 5 salmpler2DS
    *Albedo: Diffuse
    *specular
    *ambient_occlusion
    *roughness: shineness
    *emissive: For objects that emit light

*/
struct Material {
    sampler2D albedo;
    sampler2D specular;
    sampler2D ambient_occlusion;
    sampler2D roughness;
    sampler2D emissive;
};
uniform Material material;

/* Get Varyings from light.vert */
in Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
    vec3 view;
    vec3 world;
} fs_in;
out vec4 frag_color;

void main() {

    vec3 normal_vector = normalize(fs_in.normal);     

    // Compute (diffuse, specular, ambient, roughness, shininess, emissive)
    vec3 material_diffuse = texture(material.albedo, fs_in.tex_coord).rgb;
    vec3 material_specular = texture(material.specular, fs_in.tex_coord).rgb;
    vec3 material_ambient = material_diffuse * texture(material.ambient_occlusion, fs_in.tex_coord).r;
    float material_roughness = texture(material.roughness, fs_in.tex_coord).r;
    float material_shininess = 2.0 / pow(clamp(material_roughness, 0.001, 0.999), 4.0) - 2.0;
    vec3 material_emissive = texture(material.emissive, fs_in.tex_coord).rgb;

    frag_color = vec4(material_emissive, 1.0);
    int clamped_light_count = min(MAX_LIGHTS, light_count);
    for(int i = 0; i < clamped_light_count; i++) {
        Light light = lights[i];
        vec3 normal_vector = normalize(fs_in.normal);
        vec3 ambient = light.ambient * material_ambient;
        vec3 light_vector = (light.type == DIRECTIONAL) ? -normalize(light.direction) : normalize(light.position - fs_in.world);
        vec3 diffuse = light.diffuse * material_diffuse * max(0, dot(normal_vector, light_vector));
        vec3 view_vector = normalize(fs_in.view);
        vec3 reflected = reflect(-light_vector, normal_vector);
        vec3 specular = light.specular * material_specular * pow(max(0, dot(view_vector, reflected)), material_shininess);

        float attenuation = 1;
        if(light.type != DIRECTIONAL) {
            float d = distance(light.position, fs_in.world);
            attenuation /= (dot(light.attenuation, vec3(d * d, d, 1)));
            if(light.type == SPOT) {
                float angle = acos(dot(-light_vector, light.direction));
                attenuation *= smoothstep(light.cone_angles.y, light.cone_angles.x, angle);
            }
        }

        frag_color.rgb += ambient + attenuation * (diffuse + specular);
        frag_color.a = 1.0;
    }

}
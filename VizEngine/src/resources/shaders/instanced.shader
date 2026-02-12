#shader vertex
#version 460 core

// Chapter 35: Instanced rendering shader
// Per-vertex attributes (from mesh VBO)
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aTexCoords;
layout(location = 4) in vec3 aTangent;
layout(location = 5) in vec3 aBitangent;

// Per-instance attributes (from instance VBO, 4 vec4s = one mat4)
layout(location = 6) in vec4 aInstanceModel0;
layout(location = 7) in vec4 aInstanceModel1;
layout(location = 8) in vec4 aInstanceModel2;
layout(location = 9) in vec4 aInstanceModel3;

out vec3 v_WorldPos;
out vec3 v_Normal;
out vec2 v_TexCoords;

uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    // Reconstruct model matrix from per-instance attributes
    mat4 instanceModel = mat4(
        aInstanceModel0,
        aInstanceModel1,
        aInstanceModel2,
        aInstanceModel3
    );

    vec4 worldPos = instanceModel * aPos;
    v_WorldPos = worldPos.xyz;

    // Compute normal matrix from instance model (for uniform scaling this is sufficient)
    mat3 normalMatrix = mat3(instanceModel);
    v_Normal = normalize(normalMatrix * aNormal);

    v_TexCoords = aTexCoords;

    gl_Position = u_Projection * u_View * worldPos;
}


#shader fragment
#version 460 core

out vec4 FragColor;

in vec3 v_WorldPos;
in vec3 v_Normal;
in vec2 v_TexCoords;

// Simple directional lighting for instanced objects
uniform vec3 u_DirLightDirection;
uniform vec3 u_DirLightColor;
uniform vec3 u_ViewPos;
uniform vec3 u_ObjectColor;

void main()
{
    vec3 N = normalize(v_Normal);
    vec3 L = normalize(-u_DirLightDirection);
    vec3 V = normalize(u_ViewPos - v_WorldPos);
    vec3 H = normalize(V + L);

    // Ambient
    vec3 ambient = 0.15 * u_ObjectColor;

    // Diffuse (Lambertian)
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * u_DirLightColor * u_ObjectColor;

    // Specular (Blinn-Phong for simplicity)
    float spec = pow(max(dot(N, H), 0.0), 32.0);
    vec3 specular = spec * u_DirLightColor * 0.3;

    vec3 color = ambient + diffuse + specular;
    FragColor = vec4(color, 1.0);
}

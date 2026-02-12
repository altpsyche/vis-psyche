#shader vertex
#version 460 core

// Chapter 32: Simple solid-color shader for stencil outlines
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aTexCoords;
layout(location = 4) in vec3 aTangent;
layout(location = 5) in vec3 aBitangent;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * aPos;
}


#shader fragment
#version 460 core

out vec4 FragColor;

uniform vec4 u_OutlineColor;

void main()
{
    FragColor = u_OutlineColor;
}

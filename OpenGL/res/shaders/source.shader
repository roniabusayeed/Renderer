#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 textureCoord;

out vec4 v_color;
out vec2 v_textureCoord;
void main()
{
    v_color = color;
    v_textureCoord = textureCoord;
    gl_Position = vec4(position, 1.0f);
}

#shader fragment
#version 330 core
out vec4 fragColor;

in vec4 v_color;
in vec2 v_textureCoord;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform float u_ratio;
void main()
{
    vec4 color1 = texture(u_texture1, v_textureCoord);
    vec4 color2 = texture(u_texture2, vec2(v_textureCoord.s, v_textureCoord.t));

    fragColor = mix(color1, color2, u_ratio);
}
#version 130

in vec4 color;
in vec2 texCoord;
in vec2 pos;

out vec4 fragColor;

uniform sampler2D tex;
uniform float pos_x = 0.0;
uniform float pos_y = 0.0;
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0); // Color of the light
uniform float lightRadius = .95; // Radius of the light effect
uniform vec3 ambientColor = vec3(0.75, 1.0, 0.75); // Ambient light color

void main(void)
{
    vec4 texColor = texture2D(tex, texCoord) * color;

    // Calculate the distance from the light source
    vec2 lightPos = vec2(pos_x, pos_y);
    vec2 res = vec2(400,200);
    float distance = length(lightPos/res.xy - gl_FragCoord.xy/res.xy);

    // Calculate the light intensity based on distance
    float intensity = 1.0 - clamp(distance/lightRadius, 0.0, 1.0);

    // Combine the light color with the texture color
    vec3 lighting = ambientColor * lightColor * intensity;

    // Output the final color
    fragColor = vec4(texColor.rgb * lighting, texColor.a);
}

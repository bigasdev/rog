#version 130

in vec4 color;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D tex;
uniform vec2 lightPos = vec2(2.0, 3.0); // Position of the light source
uniform vec3 lightColor = vec3(0.5, 0.25, 0.0); // Color of the light
uniform float lightRadius = 2.0; // Radius of the light effect
uniform vec3 ambientColor = vec3(0.25, 0.25, 0.25); // Ambient light color

void main(void)
{
    vec4 texColor = texture2D(tex, texCoord) * color;

    // Calculate the distance from the light source
    vec2 fragPos = gl_FragCoord.xy;
    float distance = length(lightPos - fragPos);

    // Calculate the light intensity based on distance
    float intensity = 1.0 - clamp(distance / lightRadius, 0.0, 1.0);

    // Combine the light color with the texture color
    vec3 lighting = ambientColor + lightColor * intensity;

    // Output the final color
    fragColor = vec4(texColor.rgb * lighting, texColor.a);
}

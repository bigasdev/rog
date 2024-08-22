#version 120

// The texture of the sprite
uniform sampler2D tex;

// The position of the light source in screen coordinates
uniform vec2 lightPos;

// The color of the light
uniform vec3 lightColor;

// The intensity of the light
uniform float lightIntensity;

// The radius of the light's effect
uniform float lightRadius;

// Varying variables passed from the vertex shader
varying vec2 texCoord;
varying vec4 color;

void main() {
    // Sample the texture color
    vec4 texColor = texture2D(tex, texCoord);

    // Calculate the distance from the current fragment to the light source
    float distance = length(gl_FragCoord.xy - lightPos);

    // Calculate the attenuation (how light intensity decreases with distance)
    float attenuation = clamp(1.0 - (distance / lightRadius), 0.0, 1.0);

    // Calculate the final light color based on distance, light color, and intensity
    vec3 finalLightColor = lightColor * lightIntensity * attenuation;

    // Apply the lighting to the texture color
    vec3 finalColor = texColor.rgb * finalLightColor;

    // Set the output color of the fragment
    gl_FragColor = vec4(finalColor, texColor.a) * color;
}

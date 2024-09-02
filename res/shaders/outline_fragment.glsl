#version 130

in vec4 color;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D tex;
uniform vec4 outlineColor = vec4(1.0, 1.0, 1.0, 1.0); // Default white color
uniform float outlineThickness = 1.0; // Default thickness of 1

void main(void)
{
    vec4 texColor = texture2D(tex, texCoord);

    // If the pixel is not transparent, draw it normally
    if(texColor.a > 0.0) {
        fragColor = texColor * color;
    } else {
        // Check neighboring pixels for edges
        float alphaSum = 0.0;
        for (float x = -outlineThickness; x <= outlineThickness; x++) {
            for (float y = -outlineThickness; y <= outlineThickness; y++) {
                vec2 offset = vec2(x, y) / vec2(textureSize(tex, 0));
                alphaSum += texture2D(tex, texCoord + offset).a;
            }
        }

        // If any neighboring pixels are not transparent, draw the outline
        if (alphaSum > 0.0) {
            fragColor = outlineColor;
        }
    }
}

#version 120

// Attributes from the CPU
attribute vec2 gpu_Vertex;    // Vertex position
attribute vec2 gpu_TexCoord;  // Texture coordinates
attribute vec4 gpu_Color;     // Vertex color

// Varyings passed to the fragment shader
varying vec2 texCoord;
varying vec4 color;

void main() {
    // Pass texture coordinates and color to the fragment shader
    texCoord = gpu_TexCoord;
    color = gpu_Color;

    // Transform the vertex position and pass it to the rasterizer
    gl_Position = gl_ModelViewProjectionMatrix * vec4(gpu_Vertex, 0.0, 1.0);
}

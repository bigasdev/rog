#version 130

attribute vec3 gpu_Vertex;
attribute vec2 gpu_TexCoord;
attribute vec4 gpu_Color;

varying vec4 color;
varying vec2 texCoord;

void main(void)
{
	color = gpu_Color;
	texCoord = gpu_TexCoord;
	gl_Position = vec4(gpu_Vertex.xy, 0.0, 1.0);
}

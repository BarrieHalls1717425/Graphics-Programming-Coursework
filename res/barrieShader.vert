#version 400

//------------------------------------------------------------------------------------------
//similar to the ShaderToon.vert from the labs,
//as I struggled to write one on my own off the top of my head
//and this suited what I was going for.
//So, I am stating here that I utilised that lab, in case this could be seen as plagiarism.
//--------------------------------------------------------------------------------------------

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;
varying vec3 normal;
uniform mat4 transform;

void main()
{
	normal = VertexNormal;
	gl_Position = transform * vec4(VertexPosition, 1.0);
}


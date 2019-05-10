//Version number

#version 400

//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

//Uniform variable
//uniform float randColourX;
//uniform float randColourY;
//uniform float randColourZ;
 
void main()
{
//Setting each vector component to uniform variable then setting final colour
	vec4 color;
	color = vec4(1, 0.5, 0, 0);
    fragcolor = color;
}
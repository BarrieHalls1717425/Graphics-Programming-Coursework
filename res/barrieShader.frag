//#version 400

uniform vec3 heatIntensity;
//uniform vec3 colourChange;

varying vec3 normal;

void main()
{
	//--------------------------------------------------------------------------------------------
	//should somewhat simulate what would be seen when viewing something through a thermal camera
	//--------------------------------------------------------------------------------------------

	float intensity;
	vec4 colour;
	intensity = dot(heatIntensity, normal);

	//hot
	if (intensity > 0.95)
		colour = vec4(1.0,0,0,0.1);

	//mild
	else if (intensity > 0.45)
		colour = vec4(0.0,0.8,0.0,1.0);

	//warm
	else if (intensity > 0.65)
		colour = vec4(0.8,0.8,0.0,1.0);

	//cold
	else if (intensity > 0.25)
		colour = vec4(0.0,0.5,0.4,1.0);

	//colder
	else if (intensity > 0.05)
		colour = vec4(0.5,0.0,0.5,1.0);

	//colder still
	else if (intensity > 0.025)
		colour = vec4(0.3,0.0,1.0,1.0);

	//freezing
	else
		colour = vec4(0.0,0.0,0.8,1.0);
	
	gl_FragColor = colour;
}


#version 430

in vec3 reflect;
in vec3 rubtex;

uniform samplerCube cube_texture;
uniform samplerCube cube_texture2;
uniform bool drawRcube;
uniform bool rubix;
uniform int col;
out vec4 fragColour;
void main()
{
	if (drawRcube == false)
	{
		fragColour = texture(cube_texture, reflect);
	}

	//red
	else if(col == 1)
	{
		fragColour = vec4(1.0, 0.0, 0.0, 1.0);
	}

	//white
	else if(col == 2)
	{
		fragColour = vec4(1.0, 1.0, 1.0, 1.0);
	}

	//yellow
	else if(col == 3)
	{
		fragColour = vec4(1.0, 1.0, 0.0, 1.0);
	}

	else if(col == 4)
	{
		fragColour = vec4(0.0, 0.0, 1.0, 1.0);
	}

}
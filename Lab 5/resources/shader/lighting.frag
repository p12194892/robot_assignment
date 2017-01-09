#version 430

in vec3 pos;
in vec2 texCoord;

//Textures for cube texturing
uniform samplerCube cube_texture; // Bind to texture unit 0
uniform samplerCube cube_texture2; //Bind to texture unit 1

//Uniform bools
uniform bool drawRcube;
uniform bool bDrawRubix; 
uniform int col;

out vec4 fragColour;

void main()
{
	//If we are drawing the room
	if (drawRcube == true)
	{
		fragColour = texture(cube_texture, pos);
	}

	//Drawing m_box2
	else if (bDrawRubix == true)
	{
		fragColour = texture(cube_texture2, pos);
	}

	//Drawing everything else
	else if(drawRcube == false && bDrawRubix == false) 
	{	
		if(col == 0)
		{
			fragColour = vec4(0.0, 1.0, 0.0, 0.0);
		}

		//red
		if(col == 1)
		{
			fragColour = vec4(1.0, 0.0, 0.0, 1.0);
		}

		//white
		if(col == 2)
		{
			fragColour = vec4(1.0, 1.0, 1.0, 1.0);
		}

		//yellow
		if(col == 3)
		{
			fragColour = vec4(1.0, 1.0, 0.0, 1.0);
		}

		if(col == 4)
		{
			fragColour = vec4(0.0, 0.0, 1.0, 1.0);
		}

		if(col == 5)
		{
			fragColour = vec4(1.0, 0.0, 1.0, 1.0);
		}

		if(col == 6)
		{
			fragColour = vec4(1.0, 0.0, 1.0, 0.0);
		}
	}
}
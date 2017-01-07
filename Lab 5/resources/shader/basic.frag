#version 430

in vec3 pos;
in vec2 texCoord;

uniform sampler2D tex; // Bind to texture unit 0
uniform sampler2D mousetexture; //Bind to texture unit 1

uniform samplerCube cube_texture; // Bind to texture unit 2

uniform samplerCube cube_texture2; //Bind to texture unit 3

uniform bool drawRcube;
uniform int col;
uniform bool bSplashScreenState;
uniform bool bDrawRubix; //Test
uniform bool bPattern; //Test

out vec4 fragColour;

void main()
{
	if(bSplashScreenState == true)
	{
		fragColour = texture2D(tex,texCoord);
	}

	else if (bSplashScreenState == false)
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

		else if (bPattern == true)
		{
			fragColour = texture2D(mousetexture,texCoord);
		}

		//Drawing everything else
		else if(drawRcube == false && bDrawRubix == false && bPattern == false)
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
}
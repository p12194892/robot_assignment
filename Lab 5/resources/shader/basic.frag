#version 430

in vec3 pos;
in vec2 texCoord;

//Textures for Menu and GUI
uniform sampler2D tex; // Bind to texture unit 0
uniform sampler2D menutexture; //Bind to texture unit 1
uniform sampler2D buttontex; //Bind to texture unit 2
uniform sampler2D exitButtonTex; //Bind to texture unit 3
uniform sampler2D moreButtonTex; //Bind to texture unit 4
uniform sampler2D controlTex; //Bind to texture unit 5
uniform sampler2D buttonBackTex; //Bind to texture unit 6

//uniform bools
uniform bool bSplashScreenState;
uniform bool bbuttontexture; //Test
uniform bool bMenu; //new
uniform bool bexitButton;
uniform bool bmoreButton;
uniform bool bcontrolScreen;
uniform bool bbackbutton;

out vec4 fragColour;

void main()
{
	if(bSplashScreenState == true)
	{
		fragColour = texture2D(tex,texCoord);
	}

	else if (bSplashScreenState == false)
	{
		if(bMenu == true && bbuttontexture == false && bexitButton == false && bmoreButton == false && bcontrolScreen == false && bbackbutton == false)
		{
			fragColour = texture2D(menutexture,texCoord);
		}

		else if (bbuttontexture == true && bMenu == false && bexitButton == false && bmoreButton == false && bcontrolScreen == false && bbackbutton == false)
		{
			fragColour = texture2D(buttontex,texCoord);
		}

		else if (bbuttontexture == false && bMenu == false && bexitButton == true && bmoreButton == false && bcontrolScreen == false && bbackbutton == false)
		{
			fragColour = texture2D(exitButtonTex,texCoord);
		}

		else if (bbuttontexture == false && bMenu == false && bexitButton == false && bmoreButton == true && bcontrolScreen == false && bbackbutton == false)
		{
			fragColour = texture2D(moreButtonTex,texCoord);
		}

		else if(bbuttontexture == false && bMenu == false && bexitButton == false && bmoreButton == false && bcontrolScreen == true && bbackbutton == false)
		{
			fragColour = texture2D(controlTex,texCoord);
		}

		else if(bbuttontexture == false && bMenu == false && bexitButton == false && bmoreButton == false && bcontrolScreen == false && bbackbutton == true)
		{
			fragColour = texture2D(buttonBackTex,texCoord);
		}
	}
		
}
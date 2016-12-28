#version 430
//new lighting stuff
//in vec3 vertPos;
//in vec3 N;
//in vec3 lightPos;

//uniform vec3 Kd;   //Diffuse reflectivity
//uniform vec3 Ka;  //Ambient reflectivity
//uniform vec3 Ks;  //Specular reflectivity
//float shine; //Specular shininess factor

//uniform vec3 La; // Ambient light intensity
//uniform vec3 Ld; // Diffuse light intensity
//uniform vec3 Ls; //Specular light intensity

in vec3 reflect;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D tex2;


//in vec3 rubtex;

uniform samplerCube cube_texture;
uniform bool drawRcube;
uniform bool rubix;
uniform int col;
uniform bool bSplashScreenState;
out vec4 fragColour;
uniform bool button;
void main()
{

	if(bSplashScreenState == true)
	{

		//if(button == true)
		// {
		//	 fragColour = texture(tex2,texCoord);
		// }

		//else
	//	{
			fragColour = texture(tex,texCoord);
		//}
	}

	else 
	{
		//If we are drawing the room
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




	/*	//lighting equation NEW
		//Calculate the light vector (Light Source)
	   vec3 L = normalize(lightPos - vertPos);  
	   //Eye coordinates, eye pos is (0,0,0)
		vec3 v = normalize(-vertPos);
	   //Reflect factor
		//vec3 r = reflect(-L, N);
		vec3 r = -reflect(L, N);
	
		//Ambient
		vec3 ambient = Ka * La;

		//Diffuse	
		//float SDotN = max(dot(N,L), 0.0);
		float SDotN = max(dot(L,N), 0.0);
		vec3 diffuse = Ld * Kd * SDotN;
	
		 //Specular	
		 vec3 spec = vec3(0.0);
		if(SDotN > 0.0)
		{
		
			spec = Ls * Ks *  pow(max(dot(r,v), 0.0 ),  30.0f);
		}
		
		fragColour = vec4(ambient + diffuse + spec, 1.0);
		*/
}
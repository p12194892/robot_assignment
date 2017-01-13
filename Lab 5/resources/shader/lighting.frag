#version 430

//Vertex positions
in vec3 pos;
//Texture coordinates
in vec2 texCoord;

//Textures for cube texturing
uniform samplerCube cube_texture; // Bind to texture unit 0
uniform samplerCube cube_texture2; //Bind to texture unit 1
uniform samplerCube cube_texture3; //Bind to texture unit 2
uniform sampler2D spheretexture; //Bind to texture unit 3
uniform sampler2D torusTexture; //Bind to texture unit 4
uniform sampler2D cylinderTexture; //Bind to texture unit 5
uniform samplerCube robotTexture; // Bind to texture unit 6
uniform sampler2D starTexture; //Bind to texture unit 7

//Uniform bools
uniform bool drawRcube;
uniform bool bDrawRubix; 
uniform int col;
uniform bool bDrawPattern;
uniform bool bsphere;
uniform bool btorus;
uniform bool bcylinder;
uniform bool bRobot;
uniform bool bStar;

//Normals
//in vec3 Normal;

//Lighting NEW
//Struct that makes the light

/*struct Light 
{ 
    vec3 position; 
    vec3 direction; 
    float cutOff; 
    float outerCutOff; 
      
    float constant; 
    float linear; 
    float quadratic; 
      
    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular; 
}; */

//Material object
/*struct Material
{
	sampler2D diffuse;
	float shininess;
	sampler2D  specular;
};*/

//Camera Position
//uniform vec3 cameraPosition;

//Light information
//uniform Light light;

//Material
//uniform Material material;

//Fragment Colour
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

	else if (bDrawPattern == true)
	{
		fragColour = texture(cube_texture3, pos);
	}

	else if(bsphere == true)
	{
		fragColour = texture2D(spheretexture,texCoord);
	}

	else if (btorus == true)
	{
	    fragColour = texture2D(torusTexture,texCoord);
	}

	else if(bcylinder == true)
	{
		 fragColour = texture2D(cylinderTexture,texCoord);
	}

	else if (bRobot == true)
	{
		fragColour = texture(robotTexture, pos);
	}

	else if(bStar == true)
	{
		fragColour = texture2D(starTexture,texCoord);
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
	//Ambient term
//	vec3 ambient = light.ambient * vec3(texture(material.diffuse,texCoord));
	
	//Diffuse term
/*	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light.position - pos);
	float difference = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = light.diffuse * difference * vec3(texture(material.diffuse,texCoord));*/

	//Specular term
/*	vec3 viewDirection = normalize(cameraPosition - pos);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0 ), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular,texCoord));*/

	//SpotLight
/*	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;*/
		
	//Attenuation
/*	float distance = length(light.position - pos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;*/
	
	/*vec3 result = (ambient + diffuse + specular);
	fragColour = vec4(result, 1.0f);	*/

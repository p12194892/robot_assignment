#version 430

//Vertex positions
in vec3 pos;

//Texture coordinates
in vec2 texCoord;

//Normals
in vec3 Normal;

//Model Matrix
uniform mat4 M;

//Camera Position
uniform vec3 cameraPosition;

//Textures for cube texturing
uniform sampler2D cube_texture; // Bind to texture unit 0
uniform sampler2D cube_texture2; //Bind to texture unit 1
uniform sampler2D cube_texture3; //Bind to texture unit 2
uniform sampler2D spheretexture; //Bind to texture unit 3
uniform sampler2D torusTexture; //Bind to texture unit 4
uniform sampler2D cylinderTexture; //Bind to texture unit 5
uniform sampler2D robotTexture; // Bind to texture unit 6
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

//Lighting
struct Light 
{    
    vec3 position; 
    vec3 direction; 
    float cutOff; 
    float outerCutOff; 
      
    float constant; 
    float linear; 
    float quadratic; 
      
    vec3 ambient; 
	vec3 intensities;
}; 

//Light information
uniform Light light[5];

//Fragment Colour
out vec4 fragColour;

//Sending sampler2D
vec4 calculateLight(Light light, sampler2D materialTex, vec2 texCoord, vec3 Normal, vec3 pos, vec3 cameraPosition)
{
	vec4 surfaceColor = texture(materialTex, texCoord);

	//Ambient term
	vec3 ambient = light.ambient * surfaceColor.rgb * light.intensities;

	//Diffuse term
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light.position - pos);
	float difference = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = difference * surfaceColor.rgb *light.intensities ;

	//Specular term
	vec3 viewDirection = normalize(cameraPosition - pos);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0 ), 5.0f);
	vec3 specular = light.intensities * spec * surfaceColor.rgb;
	
	//SpotLight
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	//Attenuation
	float distance = length(light.position - pos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular);
	return vec4(result, 1.0);
}


void main()
{
 vec4 newLight;

	//Drawing m_box2
	 if (bDrawRubix == true)
	{
		newLight += calculateLight(light[0],cube_texture2, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[1],cube_texture2, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[2],cube_texture2, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[3],cube_texture2, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[4],cube_texture2, texCoord, Normal, pos, cameraPosition);
		fragColour = newLight;
	
	}

	else if (bDrawPattern == true)
	{
		newLight += calculateLight(light[0],cube_texture3, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[1],cube_texture3, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[2],cube_texture3, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[3],cube_texture3, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[4],cube_texture3, texCoord, Normal, pos, cameraPosition);
		fragColour = newLight;
	}

	else if(bsphere == true)
	{
	  newLight += calculateLight(light[0],spheretexture, texCoord, Normal, pos, cameraPosition);
	  newLight += calculateLight(light[1],spheretexture, texCoord, Normal, pos, cameraPosition);
	  newLight += calculateLight(light[2],spheretexture, texCoord, Normal, pos, cameraPosition);
	  newLight += calculateLight(light[3],spheretexture, texCoord, Normal, pos, cameraPosition);
	  newLight += calculateLight(light[4],spheretexture, texCoord, Normal, pos, cameraPosition);
	  fragColour = newLight;
	}

	else if (btorus == true)
	{
	  	newLight += calculateLight(light[0],torusTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[1],torusTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[2],torusTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[3],torusTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[4],torusTexture, texCoord, Normal, pos, cameraPosition);
		fragColour = newLight;
	}
	

	else if(bcylinder == true)
	{
		newLight += calculateLight(light[0],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[1],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[2],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[3],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[4],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		fragColour = newLight;
	}

	else if (bRobot == true)
	{
		newLight +=  calculateLight(light[0],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		newLight +=  calculateLight(light[1],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		newLight +=  calculateLight(light[2],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		newLight +=  calculateLight(light[3],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		newLight +=  calculateLight(light[4],cylinderTexture, texCoord, Normal, pos, cameraPosition);
		fragColour = newLight;
	}

	else if(bStar == true)
	{
		newLight += calculateLight(light[0],starTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[1],starTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[2],starTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[3],starTexture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[4],starTexture, texCoord, Normal, pos, cameraPosition);
		fragColour = newLight;
	}

	//If we are drawing the room
	else if (drawRcube == true)
	{	
		newLight += calculateLight(light[0],cube_texture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[1],cube_texture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[2],cube_texture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[3],cube_texture, texCoord, Normal, pos, cameraPosition);
		newLight += calculateLight(light[4],cube_texture, texCoord, Normal, pos, cameraPosition);
		fragColour = newLight;
	}
}

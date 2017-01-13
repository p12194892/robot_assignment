#version 430

//Vertex Position
in vec3 vertPosition;

//Texture Coordinates
in vec2 fragTexCoord;

//Vertex Normals
in vec3 vertNormal;

//Camera M*V*P
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 pos; //Vertex Position in eye coords
out vec2 texCoord; //Texture Coordinates
out vec3 Normal; //The transformed normal


void main()
{
	 //Texture data 
	 texCoord = fragTexCoord;	

	 //Vertex data
	 pos = vec3(M * vec4(vertPosition,1.0)); 

	 //Normals
	 Normal = mat3(transpose(inverse(M))) * vertNormal;

	 //Transform from local to world to camera to NDCs
	 gl_Position = MVP * vec4(vertPosition, 1.0);

}

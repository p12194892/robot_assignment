#version 430

in vec3 vertPosition;
in vec2 fragTexCoord;
//in vec3 vertNormal;

uniform mat4 MVP;
//uniform mat4 M;
///uniform mat4 V;
//uniform mat4 P;

out vec3 pos;
out vec2 texCoord;
//out vec3 Normal; 

void main()
{
	 //Texture data 
	 texCoord = fragTexCoord;	

	 //Transform from local to world to camera to NDCs
	 gl_Position = MVP * vec4(vertPosition, 1.0);

	 //Vertex data
	 pos = vertPosition;

	 //Normals
	// Normal = mat3(transpose(inverse(M))) * vertNormal;

}

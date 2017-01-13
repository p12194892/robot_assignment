#version 430


in vec3 vertPosition;
in vec2 fragTexCoord;

uniform mat4 MVP;

out vec3 pos;
out vec2 texCoord;

void main()
{
	//Texture data
	 texCoord = fragTexCoord;
	 //Vertex data
	 pos = vertPosition;
	 //Transform from local to world to camera to NDCs
	 gl_Position = MVP * vec4(vertPosition, 1.0);

}

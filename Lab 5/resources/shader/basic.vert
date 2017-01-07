#version 430

in vec3 vertPosition;
//in vec3 VertexNormal;
uniform mat4 MVP;
in vec2 fragTexCoord;

out vec3 pos;
out vec2 texCoord;

void main()
{
	 texCoord = fragTexCoord;
	 pos = vertPosition;
	 //Transform from local to world to camera to NDCs
	 gl_Position = MVP * vec4(vertPosition, 1.0);

}

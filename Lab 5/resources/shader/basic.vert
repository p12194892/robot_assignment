#version 430

in vec3 vertPosition;
uniform mat4 MVP;
out vec3 reflect;


   //normalised screen 
   //coordinates

//in vec3  vertColour;


void main()
{
	reflect = vertPosition;
	//Transform from local to world to camera to NDCs
	gl_Position = MVP * vec4(vertPosition, 1.0);

}

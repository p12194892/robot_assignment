#version 430

in vec3 vertPosition;
in vec3 VertexNormal;
uniform mat4 MVP;
in vec2 fragTexCoord;

out vec3 reflect;
out vec2 texCoord;

//new
//out vec3 N; //Transformed normal
//out vec3 lightPos; //Light position in eye coords
//out vec3 vertPos; //Vertex position in eye coords

//new lighting stuff
//uniform vec3 LightPosition; // Light position 
//uniform mat3 NormalMatrix;
//uniform mat4 M;
//uniform mat4 V;
//uniform mat4 P;

   //new stuff
 //  vertPos = vec3(V * M * vec4(vertPosition,1.0)); 
     
 // lightPos = vec3(V * M * vec4(LightPosition,1.0));  

   //Multiply the normal
 //  N = normalize( NormalMatrix * VertexNormal);
   

void main()
{

  texCoord = fragTexCoord;
  reflect = vertPosition;

    //Transform from local to world to camera to NDCs
	gl_Position = MVP * vec4(vertPosition, 1.0);

}

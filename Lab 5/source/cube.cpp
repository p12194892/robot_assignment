#include "Cube.h"
#include "FileReader.h"

//!< Default Constructor 
Cube::Cube()
{

}

//!< Constructor
Cube::Cube(GLuint programID)
{
	FileReader* m_read = new FileReader();
	m_read->ReadFile("resources/obj/cube.obj");
	setVertrices(m_read->getVertexPoints());
	setIndices(m_read->getIndices());
	setUVs(m_read->getTexPoints());
	setNormals(m_read->getNormals());

	//make sure the program handle is the main handle
	m_programHandleID = programID;

	//Load the mesh data into the buffers
	Load(m_programHandleID);
}


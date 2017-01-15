#include "Cube.h"


//!< Default Constructor 
Cube::Cube()
{

}

//!< Constructor
Cube::Cube(GLuint programID, std::string sid, FileReader* m_read)
{
	//FileReader* m_read = new FileReader();
	
	setVertrices(m_read->getVertexPoints());
	setIndices(m_read->getIndices());
	setUVs(m_read->getTexPoints());
	setNormals(m_read->getNormals());
	
	//Set ID
	m_sMeshObjectID = sid;

	//make sure the program handle is the main handle
	m_programHandleID = programID;

	//Load the mesh data into the buffers
	Load(m_programHandleID);
}


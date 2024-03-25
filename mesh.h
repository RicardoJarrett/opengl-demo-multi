#pragma once
#include <glew.h>
#include <GLFW/glfw3.h>

#include "utility.h"

class mesh {
public:
	GLuint vertexBufferID, elementBufferID, texID, vertexArrayID;
	int size;
	mesh(vtni* data, GLuint texID);
};
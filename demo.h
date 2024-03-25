#pragma once
#include <glm/glm.hpp>

#include "loader.h"
#include "mesh.h"

#include <GLFW/glfw3.h>

class Demo {
public:
	GLFWwindow* window;
	GLint uniTrans;
	mesh* cube_mesh;
	Demo(GLFWwindow* window);
	int load_assets();
	int run();
};
#pragma once
#include <glm/glm.hpp>

#include "loader.h"
#include "mesh.h"
#include "model.h"

#include <GLFW/glfw3.h>

class Demo {
public:
	GLFWwindow* window;
	GLint uniTrans;
	mesh* cube_mesh;
	model* cube_model;
	Demo(GLFWwindow* window);
	~Demo();
	int load_assets();
	int run();
};
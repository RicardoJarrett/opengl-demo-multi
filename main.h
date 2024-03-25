#pragma once

#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int create_window(GLFWwindow** win);
int init(GLFWwindow** window);

int main();
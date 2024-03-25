#include "demo.h"

#include <iostream>

#include "utility.h"
#include "mesh.h"
#include "model.h"

#include <glm/gtc/type_ptr.hpp>

Demo::Demo(GLFWwindow* window) : window(window), cube_mesh(nullptr), uniTrans(0) {
}

void create_shaders(GLuint* vs, GLuint* fs, GLuint* shader_programme, const char* vertex_shader, const char* fragment_shader) {
	*vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vs, 1, &vertex_shader, NULL);
	glCompileShader(*vs);

	*fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fs, 1, &fragment_shader, NULL);
	glCompileShader(*fs);

	*shader_programme = glCreateProgram();
	glAttachShader(*shader_programme, *fs);
	glAttachShader(*shader_programme, *vs);
	glBindAttribLocation(*shader_programme, 0, "pos");
	glBindAttribLocation(*shader_programme, 1, "tex");
	glBindAttribLocation(*shader_programme, 2, "normal");
	glLinkProgram(*shader_programme);

	GLint testVal;
	glGetShaderiv(*vs, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE)
	{
		char infolog[1024];
		glGetShaderInfoLog(*vs, 1024, NULL, infolog);
		printf("The vertex shader failed to compile with the error:\n");
		printf(infolog);
	}
	glGetShaderiv(*fs, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE)
	{
		char infolog[1024];
		glGetShaderInfoLog(*fs, 1024, NULL, infolog);
		printf("The fragment shader failed to compile with the error:\n");
		printf(infolog);
	}
}

int Demo::load_assets() {
	std::string objPath = "C:\\Users\\ricar\\Documents\\GitHub\\opengl-demo\\opengl-demo-multi\\cube.obj";
	std::string texPath = "C:\\Users\\ricar\\Documents\\GitHub\\opengl-demo\\opengl-demo-multi\\cube.png";
	GLuint texID = 0;
	vtni cube_vtni;
	loader::create_object(&cube_vtni, objPath);
	loader::load_tex(texPath, &texID);

	cube_mesh = new mesh(&cube_vtni);
	model cube_model(cube_mesh, texID);
	GLuint cube_instance = cube_model.create_instance();
	glm::mat4 local_trans = cube_model.get_local_trans(cube_instance);

	const char* vertex_shader =
		"#version 330 core\n"
		"layout(location = 0) in vec3 pos;"
		"layout(location = 1) in vec2 tex;"
		"layout(location = 2) in vec3 normal;"
		"out vec2 v_texCoords;"
		"uniform mat4 trans;"
		"void main(){"
		"  v_texCoords = tex;"
		"  gl_Position = trans * vec4(pos, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 330 core\n"
		"in vec2 v_texCoords;"
		"uniform sampler2D intexture;"
		"layout(location = 0) out vec4 frag_colour;"
		"void main(){"
		//"  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);"
		"  frag_colour = texture(intexture, v_texCoords);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint shader_programme = glCreateProgram();

	create_shaders(&vs, &fs, &shader_programme, vertex_shader, fragment_shader);
	glUseProgram(shader_programme);
	uniTrans = glGetUniformLocation(shader_programme, "trans");
	glUniform1i(glGetUniformLocation(shader_programme, "intexture"), 0);

	return 0;
}

float rotation = 0.0f;
glm::mat4 trans = glm::mat4(1.0f);

float x_rot = 0.0f;
float y_rot = 0.0f;
float z_rot = 0.0f;

float x_spd = 0.1f;
float y_spd = 0.05f;
float z_spd = 0.03f;

extern float x_pos;
extern float y_pos;
extern float z_pos;

extern float speed;

void do_rotate() {
	x_rot += x_spd;
	y_rot += y_spd;
	z_rot += z_spd;
	trans = glm::mat4(1.0f);

	trans = glm::translate(trans, glm::vec3(x_pos, y_pos, z_pos));
	trans = glm::rotate(trans, glm::radians(x_rot), glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(y_rot), glm::vec3(0.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(z_rot), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(0.25, 0.25, 0.25));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
	//trans *= proj;
}

int Demo::run() {
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		do_rotate();
		glBindVertexArray(cube_mesh->vertexArrayID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_mesh->elementBufferID);
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		glDrawElements(GL_TRIANGLES, cube_mesh->size, GL_UNSIGNED_INT, nullptr);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
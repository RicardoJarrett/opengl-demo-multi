#pragma once
#include "mesh.h"
#include <glm/glm.hpp>
#include <vector>

struct model_instance {
	GLuint id, shader_id;
	glm::mat4 local_transform, world_transform;
	glm::mat4 get_local_trans();
	glm::mat4 get_world_trans();
	void set_local_trans(glm::mat4 trans);
	void set_world_trans(glm::mat4 trans);
	bool draw_enabled;
};

class model{
private:
	GLuint tex;
	mesh* meshp;
	GLuint i_counter;
	std::vector<model_instance> instances;
public:
	model(mesh* mesh, GLuint tex);
	GLuint create_instance(GLuint shader_id);
	glm::mat4 get_local_trans(GLuint instance_id);
	void set_local_trans(GLuint instance_id, glm::mat4 trans);
	void set_world_trans(GLuint instance_id, glm::mat4 trans);
	glm::mat4 get_world_trans(GLuint instance_id);
	void rotate(GLuint instance_id, float x, float y, float z);
	void set_draw_enabled(bool enabled, GLuint instance_id);

	void render_instances();
};
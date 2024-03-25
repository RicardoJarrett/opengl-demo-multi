#pragma once
#include "mesh.h"
#include <glm/glm.hpp>
#include <vector>

struct model_instance {
	GLuint id;
	glm::mat4 local_transform, world_transform;
	glm::mat4 get_local_trans();
	glm::mat4 get_world_trans();
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
	GLuint create_instance();
	glm::mat4 get_local_trans(GLuint instance_id);
	glm::mat4 get_world_trans(GLuint instance_id);
	void set_draw_enabled(bool enabled, GLuint instance_id);
};
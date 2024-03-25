#include "model.h"

model::model(mesh* meshp, GLuint tex) : meshp(meshp), tex(tex), i_counter(0) {
}

GLuint model::create_instance() {
	model_instance tInst;
	tInst.id = i_counter;
	i_counter++;
	tInst.local_transform = glm::mat4(1.0f);
	tInst.world_transform = glm::mat4(1.0f);
	instances.push_back(tInst);

	return tInst.id;
}

glm::mat4 model::get_local_trans(GLuint instance_id) {
	for (std::vector<model_instance>::iterator it = instances.begin(); it != instances.end(); it++) {
		if (it->id == instance_id) {
			return it->get_local_trans();
		}
	}
}

glm::mat4 model::get_world_trans(GLuint instance_id) {
	for (std::vector<model_instance>::iterator it = instances.begin(); it != instances.end(); it++) {
		if (it->id == instance_id) {
			return it->get_world_trans();
		}
	}
}

void model::set_draw_enabled(bool enabled, GLuint instance_id) {
	for (std::vector<model_instance>::iterator it = instances.begin(); it != instances.end(); it++) {
		if (it->id == instance_id) {
			it->draw_enabled = enabled;
		}
	}
}

glm::mat4 model_instance::get_local_trans() {
	return local_transform;
};

glm::mat4 model_instance::get_world_trans() {
	return world_transform;
};
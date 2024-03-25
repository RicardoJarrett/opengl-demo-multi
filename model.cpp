#include "model.h"

#include <glm/gtc/type_ptr.hpp>

model::model(mesh* meshp, GLuint tex) : meshp(meshp), tex(tex), i_counter(0) {
}

GLuint model::create_instance(GLuint shader_id) {
	model_instance tInst;
	tInst.id = i_counter;
	tInst.shader_id = shader_id;
	i_counter++;
	tInst.local_transform = glm::mat4(1.0f);
	tInst.world_transform = glm::mat4(1.0f);
	tInst.draw_enabled = true;
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

void model::set_local_trans(GLuint instance_id, glm::mat4 trans) {
	for (std::vector<model_instance>::iterator it = instances.begin(); it != instances.end(); it++) {
		if (it->id == instance_id) {
			it->set_local_trans(trans);
		}
	}
}

void model::set_world_trans(GLuint instance_id, glm::mat4 trans) {
	for (std::vector<model_instance>::iterator it = instances.begin(); it != instances.end(); it++) {
		if (it->id == instance_id) {
			it->set_world_trans(trans);
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

void model::render_instances() {
	glm::mat4 projection = glm::mat4(1.0f);
	
	glBindVertexArray(meshp->vertexArrayID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshp->elementBufferID);

	glDrawElements(GL_TRIANGLES, meshp->size, GL_UNSIGNED_INT, nullptr);
	for (std::vector<model_instance>::iterator it = instances.begin(); it != instances.end(); it++) {
		if (it->draw_enabled == true) {
			GLuint uniTrans = glGetUniformLocation(it->shader_id, "trans");
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(it->get_local_trans()));
			glDrawElements(GL_TRIANGLES, meshp->size, GL_UNSIGNED_INT, nullptr);
		}
	}
}

void model::rotate(GLuint instance_id, float x, float y, float z) {
	for (std::vector<model_instance>::iterator it = instances.begin(); it != instances.end(); it++) {
		if (it->id == instance_id) {
			glm::mat4 trans = it->get_local_trans();
			trans = glm::rotate(trans, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
			trans = glm::rotate(trans, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
			trans = glm::rotate(trans, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
			it->set_local_trans(trans);
		}
	}
}

glm::mat4 model_instance::get_local_trans() {
	return local_transform;
};

glm::mat4 model_instance::get_world_trans() {
	return world_transform;
};

void model_instance::set_local_trans(glm::mat4 trans) {
	local_transform = trans;
}

void model_instance::set_world_trans(glm::mat4 trans) {
	world_transform = trans;
}
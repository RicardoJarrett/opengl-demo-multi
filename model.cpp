#include "model.h"
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

model::model() {
	model_id = 0;
	mesh_id = 0;
	texture_id = 0;
	meshp = nullptr;
}

model::model(GLuint _model_id, GLuint _mesh_id, GLuint _texture_id, mesh* _meshp) {
	model_id = _model_id;
	mesh_id = _mesh_id;
	texture_id = _texture_id;
	meshp = _meshp;
}

void model::bind(GLuint shader_id) {
	if (meshp != nullptr) {
		glBindVertexArray(meshp->vertexArrayID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshp->elementBufferID);
		glUniform1i(glGetUniformLocation(shader_id, "intexture"), 0);
	}
}

glm::mat4 model_instance::get_local_transform() {
	glm::mat4 local_transform = local.translation * local.rotation * local.scale * glm::mat4(1.0f);
	return local_transform;
}

glm::mat4 model_instance::get_world_transform() {
	glm::mat4 world_transform = world.translation * world.rotation * world.scale * glm::mat4(1.0f);
	return world_transform;
}

void model_instance::render() {
	if (model_p != nullptr) {

		model_p->bind(shader_id);

		if (draw_enabled == true) {
			GLuint model = glGetUniformLocation(shader_id, "model");
			GLuint view = glGetUniformLocation(shader_id, "view");
			GLuint projection = glGetUniformLocation(shader_id, "projection");
			//glm::mat4 proj_trans = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
			glm::mat4 local_trans = get_local_transform();
			glm::mat4 world_trans = get_world_transform();
			glm::mat4 proj_trans = glm::mat4(1.0f);
			glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(local_trans));
			glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(world_trans));
			glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(proj_trans));
			glDrawElements(GL_TRIANGLES, model_p->meshp->size, GL_UNSIGNED_INT, nullptr);
		}
	}
}

model_instance::model_instance() {
	model_p = nullptr;
	shader_id = 0;
	local = rts_transformation();
	world = rts_transformation();
	draw_enabled = true;
}

model_instance::model_instance(model* _model_p, GLuint _shader_id, rts_transformation _local, rts_transformation _world, bool _draw_enabled) {
	model_p = _model_p;
	shader_id = _shader_id;
	local = _local;
	world = _world;
	draw_enabled = _draw_enabled;
}

void model_instance::local_rotate(glm::vec3 angles) {
	local.rotation = glm::rotate(local.rotation, glm::radians(angles.x), glm::vec3(1.0, 0.0, 0.0));
	local.rotation = glm::rotate(local.rotation, glm::radians(angles.y), glm::vec3(0.0, 1.0, 0.0));
	local.rotation = glm::rotate(local.rotation, glm::radians(angles.z), glm::vec3(0.0, 0.0, 1.0));
}

void model_instance::local_translate(glm::vec3 trans) {
	local.translation = glm::translate(local.translation, trans);
}

void model_instance::local_scale(glm::vec3 scale) {
	local.scale = glm::scale(local.scale, scale);
}

void model_instance::world_rotate(glm::vec3 angles) {
	world.rotation = glm::rotate(world.rotation, glm::radians(angles.x), glm::vec3(1.0, 0.0, 0.0));
	world.rotation = glm::rotate(world.rotation, glm::radians(angles.y), glm::vec3(0.0, 1.0, 0.0));
	world.rotation = glm::rotate(world.rotation, glm::radians(angles.z), glm::vec3(0.0, 0.0, 1.0));
}

void model_instance::world_translate(glm::vec3 trans) {
	world.translation = glm::translate(world.translation, trans);
}

void model_instance::world_scale(glm::vec3 scale) {
	world.scale = glm::scale(world.scale, scale);
}
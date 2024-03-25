#pragma once
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

struct lineData {
	size_t pos;
	std::string* line;
	size_t* offset;
};

struct verti {
	int position[3];
	int tex[3];
	int normal[3];
};

struct vertexf {
	float position[3];
	float tex[2];
	float normal[3];
	std::string string();
};

struct vtni {
	vertexf* vertex_list;
	int* index_list;
	int size;
	std::string string();
	void cleanup();
};
#include "utility.h"

std::string vertexf::string() {
	std::string return_string = "[" + std::to_string(position[0]) + "," + std::to_string(position[1]) + "," + std::to_string(position[2]) + "] ";
	return_string += "[" + std::to_string(tex[0]) + "," + std::to_string(tex[1]) + "] ";
	return_string += "[" + std::to_string(normal[0]) + "," + std::to_string(normal[1]) + "," + std::to_string(normal[2]) + "]";
	return return_string;
}

std::string vtni::string() {
	std::string return_string = "";
	for (int i = 0; i < size; i++) {
		return_string += vertex_list[i].string() + "\n";
	}
	return return_string;
}

void vtni::cleanup() {
	free(this);
}
#include "object_t3.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object_new::CreateCircle(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float angle,
	glm::vec3 color,
	int fragments,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color)
	};
	for (int i = 1; i < fragments + 2; i++) {
		vertices.push_back(VertexFormat(glm::vec3(corner.x + (angle * cos(i * 2.0f * M_PI / fragments)),0, corner.z + (angle * sin(i * 2.0f * M_PI / fragments))), color));
	}



	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0 };
	for (int i = 1; i < fragments + 2; i++) {
		indices.push_back(i);
	}

	square->SetDrawMode(GL_TRIANGLE_FAN);

	square->InitFromData(vertices, indices);
	return square;
}

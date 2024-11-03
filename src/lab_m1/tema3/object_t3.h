#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object_new
{
	Mesh* CreateCircle(const std::string& name, glm::vec3 leftBottomCorner, float angle, glm::vec3 color, int fragments, bool fill);
}
#pragma once

#include "Komet/Renderer/Mesh.h"
#include <memory>

namespace Komet
{
	class Primitive
	{
	public:
		static std::shared_ptr<Mesh> Cube();
	};
}


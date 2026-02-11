#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace Komet {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec2 TexCoords;
        glm::vec3 Normal;
    };

    class Mesh {
    public:
        Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
        void Draw();
    private:
        unsigned int m_VAO, m_VBO, m_EBO;
        uint32_t m_IndexCount;
    };
}
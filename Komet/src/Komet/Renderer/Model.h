#pragma once

#include "kmpch.h"

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Komet/Renderer/Shader.h"


namespace Komet {

    class Model {
    public:

        Model(const std::string& path);

        void Draw(Shader& shader);

    private:

        std::vector<Mesh> m_Meshes;
        std::string m_Directory;

        // Assimp recursive loading functions
        void loadModel(const std::string& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    };

}
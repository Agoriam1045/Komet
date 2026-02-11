#include "kmpch.h"
#include "Model.h"

namespace Komet {

    Model::Model(const std::string& path) {
        loadModel(path);
    }

    void Model::loadModel(const std::string& path) {
        Assimp::Importer importer;
        
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals| aiProcess_PreTransformVertices);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            KM_CORE_ERROR("ASSIMP ERROR: {0}", importer.GetErrorString());
            return;
        }

        m_Directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(processMesh(mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    //Translating Assimp to Komet
    Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;

            // Positions
            vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

            // Normals
            if (mesh->HasNormals())
                vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

            // Textures
            if (mesh->mTextureCoords[0])
                vertex.TexCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
            else
                vertex.TexCoords = { 0.0f, 0.0f };

            vertices.push_back(vertex);
        }

        // Indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        return Mesh(vertices, indices);
    }

    void Model::Draw(Shader& shader) {
        for (unsigned int i = 0; i < m_Meshes.size(); i++) {
            m_Meshes[i].Draw();
        }
    }
}
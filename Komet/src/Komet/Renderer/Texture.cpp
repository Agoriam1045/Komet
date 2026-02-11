#include "kmpch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

namespace Komet {
    Texture2D::Texture2D(const std::string& path) : m_FilePath(path) {

        stbi_set_flip_vertically_on_load(1);

        unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        if (data) {
            stbi_image_free(data);
            KM_CORE_INFO("Successfully loaded texture: {0} ({1}x{2})", path, m_Width, m_Height);
        }
		else KM_CORE_ERROR("stb_image failed to load: {0}. Reason: {1}", path, stbi_failure_reason());
    }

    Texture2D::~Texture2D() { glDeleteTextures(1, &m_RendererID); }

    void Texture2D::Bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
}
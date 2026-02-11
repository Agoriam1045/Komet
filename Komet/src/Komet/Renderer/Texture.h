#pragma once
#include <string>

namespace Komet {
    class Texture2D {
    public:
        Texture2D(const std::string& path);
        ~Texture2D();

        void Bind(uint32_t slot = 0) const;
        void Unbind() const;

    private:
        uint32_t m_RendererID;
        std::string m_FilePath;
        int m_Width, m_Height, m_BPP;
    };
}
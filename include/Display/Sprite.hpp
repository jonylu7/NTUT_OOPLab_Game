//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP
#include "Core/Drawable.hpp"
#include "Display/CustomizableImage.hpp"
#include "Util/Image.hpp"
#include "pch.hpp" // IWYU pragma: export

class Sprite : public Core::Drawable {
public:
    Sprite(const std::string &filepath, std::vector<float> textcoord,
           std::vector<float> uvcoord,
           std::vector<unsigned int> index = {0, 1, 2, 2, 3, 0})
        : m_Index(index),
          m_TextureCoord(textcoord),
          m_UvCoord(uvcoord) {
        m_Image = std::make_unique<Util::CustomizableImage>(filepath);
        m_Image->Init(textcoord, uvcoord, index);
    };

    ~Sprite(){};

    void Draw(const Util::Transform &transform, const float zIndex) override {
        m_Image->Draw(transform, zIndex);
    }

    void DrawUsingCamera(const Util::Transform &transform,
                         const float zIndex) override {
        m_Image->DrawUsingCamera(transform, zIndex);
    }

    void Init() { m_Image->Init(m_TextureCoord, m_UvCoord, m_Index); }

    void SetIndex(std::vector<unsigned int> index) { m_Image->SetIndex(index); }
    void DrawTest(int count, const Util::Transform &transform,
                  const float zIndex) {
        // m_Image->Draw(count,transform,zIndex);
    }

    GLuint getGLunit() { return m_Image->getTextureID(); }

private:
    std::unique_ptr<Util::CustomizableImage> m_Image;
    std::vector<float> m_TextureCoord;
    std::vector<float> m_UvCoord;
    std::vector<unsigned int> m_Index;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP

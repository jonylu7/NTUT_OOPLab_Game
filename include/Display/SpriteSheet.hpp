//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP
#include "Display/CustomizableImage.hpp"
#include "Sprite.hpp"
class SpriteSheet {
public:
    SpriteSheet(){};
    ~SpriteSheet() {}

    /**
     * @brief SpriteSheet, use Start to define a spritesheet, reading sequence
     * will be read in "row-first" order
     * @param filepath like the defination of "Image"
     * @param spriteWidth spriteWidth
     * @param spriteHeight spriteHieght
     * @param numSpirtes what's the total number of sprites in an image
     * @param spacing spacing between sprites
     *
     */
    void Start(std::string filepath, int spriteWidth, int spriteHeight,
               int numSpirtes, int spacing);

    void DrawSpriteByIndex(int index, Util::Transform trans, int zIndex) {
        m_SpriteSheet[index]->Init();
        m_SpriteSheet[index]->DrawUsingCamera(trans, zIndex);
    }
    void InitSpritByIndex(int index) { m_SpriteSheet[index]->Init(); }

    void DrawSpriteWithoutChange(int index, Util::Transform trans, int zIndex) {
        m_SpriteSheet[index]->DrawUsingCamera(trans, zIndex);
    }

    glm::vec2 getSpriteSize() {
        return glm::vec2(m_SpriteWidth, m_SpriteHeight);
    };

    GLuint getGlunitByIndex(int index) {
        m_SpriteSheet[index]->Init();
        return m_SpriteSheet[index]->getGLunit();
    }

    std::vector<float> getUVbyIndex(int index) { return m_Uv[index]; }

    static std::vector<glm::vec2> UVtoImGuiCoord(std::vector<float> UV) {
        // 0,3 & 4,1
        return std::vector<glm::vec2>{glm::vec2(UV[0], UV[1]),
                                      glm::vec2(UV[4], UV[3])};
    }

    int getSize() { return m_SpriteSheet.size(); }

private:
    std::vector<std::unique_ptr<Sprite>> m_SpriteSheet;
    std::vector<float> m_TextCoord;
    std::vector<std::vector<float>> m_Uv;
    std::vector<unsigned int> m_Index;
    int m_SpriteWidth = 0;
    int m_SpriteHeight = 0;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP

//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP
#include "Sprite.hpp"
#include "Util/CustomizableImage.hpp"
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
        m_SpriteSheet[index]->Draw(trans, zIndex);
    }

    glm::vec2 getSpriteSize() {
        return glm::vec2(m_SpriteWidth, m_SpriteHeight);
    };

private:
    std::vector<std::unique_ptr<Sprite>> m_SpriteSheet;
    std::vector<float> m_TextCoord;
    std::vector<std::vector<float>> m_Uv;
    std::vector<unsigned int> m_Index;
    int m_SpriteWidth;
    int m_SpriteHeight;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP

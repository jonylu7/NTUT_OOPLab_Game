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

    ~SpriteSheet() {}

    void DrawSpriteByIndex(int index, Util::Transform trans, int zIndex) {
        m_SpriteSheet[index]->Init();
        m_SpriteSheet[index]->Draw(trans, zIndex);
    }

private:
    std::vector<std::unique_ptr<Sprite>> m_SpriteSheet;
    std::vector<float> m_TextCoord;
    std::vector<std::vector<float>> m_Uv;
    std::vector<unsigned int> m_index;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP

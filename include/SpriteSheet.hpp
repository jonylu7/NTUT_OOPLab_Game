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
               int numSpirtes, int spacing) {

        std::shared_ptr<Util::CustomizableImage> m_SpriteSheet_Image =
            std::make_shared<Util::CustomizableImage>(filepath);

        // indecis
        m_index = {0, 1, 2, 2, 3, 0};

        // textcoord
        float coordHeight =
            spriteHeight / (float)m_SpriteSheet_Image->GetSize().y;
        float coordWidth =
            spriteWidth / (float)m_SpriteSheet_Image->GetSize().x;
        std::vector<float> coord({-(coordWidth / 2), (coordHeight / 2),  //
                                  -(coordWidth / 2), -(coordHeight / 2), //
                                  (coordWidth / 2), -(coordHeight / 2),  //
                                  (coordWidth / 2), (coordHeight / 2)});

        int currentX = 0;
        int currentY = m_SpriteSheet_Image->GetSize().y - spriteHeight;

        // uvcoords
        for (int i = 0; i < numSpirtes; i++) {
            float topY = (currentY + spriteHeight) /
                         (float)m_SpriteSheet_Image->GetSize().y;
            float rightX = (currentX + spriteWidth) /
                           (float)m_SpriteSheet_Image->GetSize().x;
            float leftX = currentX / (float)m_SpriteSheet_Image->GetSize().x;
            float bottomY = currentY / (float)m_SpriteSheet_Image->GetSize().y;

            if (currentX >= m_SpriteSheet_Image->GetSize().x) {
                currentX = 0;
                currentY -= spriteHeight + spacing;
            }

            m_Uv.push_back(std::vector<float>({leftX, bottomY, //
                                               leftX, topY,    //
                                               rightX, topY,   //
                                               rightX, bottomY}));

            m_SpriteSheet.push_back(
                std::make_unique<Sprite>(filepath, coord,
                                         std::vector<float>{leftX, bottomY, //
                                                            leftX, topY,    //
                                                            rightX, topY,   //
                                                            rightX, bottomY}));
            currentX += spriteWidth + spacing;
        }
    }
    ~SpriteSheet() {}

    void DrawSpriteByIndex(int index, Util::Transform trans, int zIndex) {
        m_SpriteSheet[index]->Init(m_TextCoord, m_Uv[index], m_index);
        m_SpriteSheet[index]->Draw(trans, zIndex);
    }

private:
    std::vector<std::unique_ptr<Sprite>> m_SpriteSheet;
    std::vector<float> m_TextCoord;
    std::vector<std::vector<float>> m_Uv;
    std::vector<unsigned int> m_index;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP

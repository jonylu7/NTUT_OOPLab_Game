//
// Created by 盧威任 on 3/1/24.
//
#include "SpriteSheet.hpp"

void SpriteSheet::Start(std::string filepath, int spriteWidth, int spriteHeight,
                        int numSpirtes, int spacing) {

    std::shared_ptr<Util::CustomizableImage> m_SpriteSheet_Image =
        std::make_shared<Util::CustomizableImage>(filepath);

    // textcoord
    float coordHeight = spriteHeight / (float)m_SpriteSheet_Image->GetSize().y;
    float coordWidth = spriteWidth / (float)m_SpriteSheet_Image->GetSize().x;
    std::vector<float> coord({-(coordWidth / 2), (coordHeight / 2),  //
                              -(coordWidth / 2), -(coordHeight / 2), //
                              (coordWidth / 2), -(coordHeight / 2),  //
                              (coordWidth / 2), (coordHeight / 2)});

    int currentX = 0;
    int currentY = m_SpriteSheet_Image->GetSize().y - spriteHeight;

    // uvcoords
    for (int i = 0; i < numSpirtes; i++) {
        float topY =
            (currentY + spriteHeight) / (float)m_SpriteSheet_Image->GetSize().y;
        float rightX =
            (currentX + spriteWidth) / (float)m_SpriteSheet_Image->GetSize().x;
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

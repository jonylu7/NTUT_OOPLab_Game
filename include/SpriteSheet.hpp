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
    void Start(std::string filepath, int spriteWidth, int spriteHeight,
               int numSpirtes, int spacing) {
        m_SpriteSheet_Image =
            std::make_shared<Util::CustomizableImage>(filepath);

        m_SpriteHeight = spriteHeight;
        m_SpriteWidth = spriteWidth;

        int currentX = 0;
        int currentY = m_SpriteSheet_Image->GetSize().y - spriteHeight;

        // textcoord
        float coordHeight =
            spriteHeight / (float)m_SpriteSheet_Image->GetSize().y;
        float coordWidth =
            spriteWidth / (float)m_SpriteSheet_Image->GetSize().x;
        std::vector<float> coord({-(coordWidth / 2), (coordHeight / 2),  //
                                  -(coordWidth / 2), -(coordHeight / 2), //
                                  (coordWidth / 2), -(coordHeight / 2),  //
                                  (coordWidth / 2), (coordHeight / 2)});

        currentX += spriteWidth * 1 + spacing;
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

            // uvcoord
            std::vector<float> uv({leftX, bottomY, //
                                   leftX, topY,    //
                                   rightX, topY,   //
                                   rightX, bottomY});

            unsigned int step = unsigned(0 * 4);
            std::vector<unsigned int> index = {0 + step, 1 + step, 2 + step,
                                               2 + step, 3 + step, 0 + step};

            m_TextCoord.insert(m_TextCoord.end(), coord.begin(), coord.end());
            m_Uv.insert(m_Uv.end(), uv.begin(), uv.end());

            m_index.push_back(index);

            m_SpriteSheet.push_back(
                std::make_unique<Sprite>(filepath, coord,
                                         std::vector<float>{leftX, bottomY, //
                                                            leftX, topY,    //
                                                            rightX, topY,   //
                                                            rightX, bottomY}));
            currentX += spriteWidth + spacing;
        }

        // m_SpriteSheet_Image->Init(m_TextCoord, m_Uv, m_index);
    }
    ~SpriteSheet() {}

    void Update() {
        float coordHeight =
            m_SpriteHeight / (float)m_SpriteSheet_Image->GetSize().y;
        float coordWidth =
            m_SpriteWidth / (float)m_SpriteSheet_Image->GetSize().x;
        std::vector<float> coord({-(coordWidth / 2), (coordHeight / 2),  //
                                  -(coordWidth / 2), -(coordHeight / 2), //
                                  (coordWidth / 2), -(coordHeight / 2),  //
                                  (coordWidth / 2), (coordHeight / 2)});

        Util::Transform trans;
        trans.translation.x = -400;

        int currentX = 0;
        int currentY = m_SpriteSheet_Image->GetSize().y - m_SpriteHeight;

        unsigned int step = unsigned(0 * 4);
        std::vector<unsigned int> index = {0 + step, 1 + step, 2 + step,
                                           2 + step, 3 + step, 0 + step};

        for (int i = 0; i < 13; i++) {

            float topY = (currentY + m_SpriteHeight) /
                         (float)m_SpriteSheet_Image->GetSize().y;
            float rightX = (currentX + m_SpriteWidth) /
                           (float)m_SpriteSheet_Image->GetSize().x;
            float leftX = currentX / (float)m_SpriteSheet_Image->GetSize().x;
            float bottomY = currentY / (float)m_SpriteSheet_Image->GetSize().y;

            std::vector<float> uv({leftX, bottomY, //
                                   leftX, topY,    //
                                   rightX, topY,   //
                                   rightX, bottomY});

            trans.translation.x += 64;
            m_SpriteSheet[i]->Init(coord, uv, index);
            m_SpriteSheet[i]->Draw(trans, 2);
            // DrawSpriteByIndex(i, trans, 2);
        }
    }

    void DrawSpriteByIndex(int index, Util::Transform trans, int zIndex) {
        unsigned int step = unsigned(3 * 4);
        /*
        std::vector<unsigned int> indexV = {0 + step, 1 + step, 2 + step,
                                            2 + step, 3 + step, 0 + step};
        m_SpriteSheet_Image->SetIndex(indexV);
         */
        m_SpriteSheet[index]->Draw(trans, zIndex);
        // m_SpriteSheet_Image->DrawTest((4), trans, zIndex);
    }

private:
    std::vector<std::unique_ptr<Sprite>> m_SpriteSheet;
    std::shared_ptr<Util::CustomizableImage> m_SpriteSheet_Image;
    std::vector<float> m_TextCoord;
    std::vector<float> m_Uv;
    std::vector<std::vector<unsigned int>> m_index;
    int m_SpriteWidth;
    int m_SpriteHeight;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP

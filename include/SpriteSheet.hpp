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
    void Start( std::string filepath, int spriteWidth,
               int spriteHeight, int numSpirtes, int spacing){
        m_SpriteSheet_Image=std::make_shared<Util::CustomizableImage>(filepath);
        int currentX = 0;
        int currentY = m_SpriteSheet_Image->GetSize().y - spriteHeight;
    /*
        for (int i = 0; i < numSpirtes; i++) {
            float topY = (currentY + spriteHeight) /
                         (float)m_SpriteSheet_Image->GetSize().y;
            float rightX = (currentX + spriteWidth) /
                           (float)m_SpriteSheet_Image->GetSize().x;
            float leftX = currentX / (float)m_SpriteSheet_Image->GetSize().x;
            float bottomY = currentY / (float)m_SpriteSheet_Image->GetSize().y;

            currentX += spriteWidth + spacing;
            if (currentX >= m_SpriteSheet_Image->GetSize().x) {
                currentX = 0;
                currentY -= spriteHeight + spacing;
            }

            //uv

        }
        */
        currentX += spriteWidth + spacing;
        float topY = (currentY + spriteHeight) /
                     (float)m_SpriteSheet_Image->GetSize().y;
        float rightX = (currentX + spriteWidth) /
                       (float)m_SpriteSheet_Image->GetSize().x;
        float leftX = currentX / (float)m_SpriteSheet_Image->GetSize().x;
        float bottomY = currentY / (float)m_SpriteSheet_Image->GetSize().y;

        std::vector<float> uv({ leftX, bottomY, //
                               leftX, topY,//
                               rightX, topY, //
                rightX, bottomY
        });

        //coord
        float coordHeight=spriteHeight/(float)m_SpriteSheet_Image->GetSize().y;
        float coordWidth=spriteWidth/(float)m_SpriteSheet_Image->GetSize().x;
        std::vector<float> coord({-(coordWidth/2), (coordHeight/2),  //
                                  -(coordWidth/2), -(coordHeight/2), //
                                  (coordWidth/2), -(coordHeight/2),  //
                                  (coordWidth/2), (coordHeight/2)});

            // index
            std::vector<unsigned int> index({
                0, 1, 2, //
                0, 2, 3, //
            });

m_SpriteSheet_Image->Init(coord,uv,index);


    }
    ~SpriteSheet() {}
    Sprite getSpriteByIndex(int index) { return m_SpriteSheet[index]; }

    void Update() {
        Util::Transform trans;
        m_SpriteSheet_Image->Draw(trans,0);
        //getSpriteByIndex(23).getTexture()->Draw(trans,0);

    }

private:
    std::vector<Sprite> m_SpriteSheet;
    std::shared_ptr<Util::CustomizableImage> m_SpriteSheet_Image;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP

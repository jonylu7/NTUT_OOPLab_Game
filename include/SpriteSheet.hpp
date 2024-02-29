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

        //textcoord
        float coordHeight=spriteHeight/(float)m_SpriteSheet_Image->GetSize().y;
        float coordWidth=spriteWidth/(float)m_SpriteSheet_Image->GetSize().x;
        std::vector<float> coord({-(coordWidth/2), (coordHeight/2),  //
                                  -(coordWidth/2), -(coordHeight/2), //
                                  (coordWidth/2), -(coordHeight/2),  //
                                  (coordWidth/2), (coordHeight/2)});

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

            //uvcoord
            std::vector<float> uv({ leftX, bottomY, //
                                   leftX, topY,//
                                   rightX, topY, //
                                   rightX, bottomY
            });

            m_TextCoord.insert(m_TextCoord.end(),coord.begin(),coord.end());
            m_Uv.insert(m_Uv.end(),m_Uv.begin(),m_Uv.end());
            m_SpriteSheet.push_back(std::make_unique<Sprite>(filepath,coord,uv));
        }

    }
    ~SpriteSheet() {}


    void Update() {
        Util::Transform trans;
        //getSpriteByIndex(23).getTexture()->Draw(trans,0);
        DrawSpriteByIndex(2,trans,0);
    }

    void DrawSpriteByIndex(int index,Util::Transform trans,int zIndex){
        m_SpriteSheet[index]->Draw(trans,zIndex);
        //m_SpriteSheet[0]->DrawTest(int(m_SpriteSheet.size()*8*12),trans,zIndex);
    }



private:
    std::vector<std::unique_ptr<Sprite>> m_SpriteSheet;
    std::shared_ptr<Util::CustomizableImage> m_SpriteSheet_Image;
    std::vector<float> m_TextCoord;
    std::vector<float> m_Uv;
    std::vector<unsigned int> m_index;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP

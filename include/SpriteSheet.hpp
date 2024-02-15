//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP
#include "Sprite.hpp"
#include "Util/Image.hpp"
class SpriteSheet{
public:
    SpriteSheet(){}
    void Start(std::shared_ptr<Util::Image> image,int spriteWidth,int spriteHeight,int numSpirtes, int spacing){
        m_SpriteSheet={};
        m_SpriteSheet_Image=image;

        int currentX = 0;
        int currentY = m_SpriteSheet_Image->getHeight() - spriteHeight;
        for (int i=0; i < numSpirtes; i++) {
            float topY = (currentY + spriteHeight) / (float)m_SpriteSheet_Image->getHeight();
            float rightX = (currentX + spriteWidth) / (float)m_SpriteSheet_Image->getWidth();
            float leftX = currentX / (float)m_SpriteSheet_Image->getWidth();
            float bottomY = currentY / (float)m_SpriteSheet_Image->getHeight();

            std::vector<glm::vec2> texCoords = {
                 glm::vec2(rightX, topY),
                 glm::vec2(rightX, bottomY),
                 glm::vec2(leftX, bottomY),
                 glm::vec2(leftX, topY)
            };
            Sprite sprite(m_SpriteSheet_Image, texCoords);
            m_SpriteSheet.push_back(sprite);

            currentX += spriteWidth + spacing;
            if (currentX >= m_SpriteSheet_Image->getWidth()) {
                currentX = 0;
                currentY -= spriteHeight + spacing;
            }
        }
    }
    ~SpriteSheet(){}
    Sprite getSpriteByIndex(int index){
        return m_SpriteSheet[index];
    }

    void Update(){
        Util::Transform trans;
        getSpriteByIndex(23).getTexture()->Draw(trans,0);
    }
private:
    std::vector<Sprite> m_SpriteSheet;
    std::shared_ptr<Util::Image> m_SpriteSheet_Image;




};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEET_HPP

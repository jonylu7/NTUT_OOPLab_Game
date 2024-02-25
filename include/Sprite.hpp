//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP
#include "Util/Image.hpp"

class Sprite {
public:
    Sprite(std::shared_ptr<Util::Image> texture) {
        /*
         * TextureCoord is the coordinate system of this sprite,
         * by default its x and y range is within 0 and 1
         * the textureCoord vector is defined counter clock wise, starting from
         * the top right corner.
         */
        m_Texture = texture;
        m_TextureCoord = {glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0),
                          glm::vec2(0, 1)

        };
    };
    Sprite(std::shared_ptr<Util::Image> texture,
           std::vector<glm::vec2> textureCoord) {
        m_Texture = texture;
        m_TextureCoord = textureCoord;
    };
    ~Sprite(){};

    std::shared_ptr<Util::Image> getTexture() { return m_Texture; };

    std::vector<glm::vec2> getTextureCoord() { return m_TextureCoord; }

private:
    std::shared_ptr<Util::Image> m_Texture;
    std::vector<glm::vec2> m_TextureCoord;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP

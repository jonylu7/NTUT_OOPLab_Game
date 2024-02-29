//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP
#include "Util/Image.hpp"
#include "Util/CustomizableImage.hpp"
#include "Core/Drawable.hpp"
#include "pch.hpp" // IWYU pragma: export

class Sprite:public Core::Drawable {
public:
    Sprite(std::string filepath,std::vector<float> textcoord,std::vector<float> uvcoord,std::vector<unsigned int> index):m_Index(index),m_Image(std::make_unique<Util::CustomizableImage>(filepath)),m_TextureCoord(textcoord),m_UvCoord(uvcoord){
        /*
         * TextureCoord is the coordinate system of this sprite,
         * by default its x and y range is within 0 and 1
         * the textureCoord vector is defined counter clock wise, starting from
         * the top right corner.
         */
        //m_Image->Init(m_TextureCoord,m_UvCoord,m_Index);
        };
    Sprite(std::string filepath,std::vector<float> textcoord,std::vector<float> uvcoord):m_Image(std::make_unique<Util::CustomizableImage>(filepath)),m_TextureCoord(textcoord),m_UvCoord(uvcoord){
              /*
         * TextureCoord is the coordinate system of this sprite,
         * by default its x and y range is within 0 and 1
         * the textureCoord vector is defined counter clock wise, starting from
         * the top right corner.
               */
              m_Image->Init(m_TextureCoord,m_UvCoord,m_Index);
          };

    ~Sprite(){};
    void Draw(const Util::Transform &transform, const float zIndex)override{
        m_Image->Draw(transform,zIndex);
    }
    void DrawTest(int count,const Util::Transform &transform, const float zIndex){
        //m_Image->Draw(count,transform,zIndex);
    }

private:
    std::shared_ptr<Util::CustomizableImage> m_Image;
    std::vector<float> m_TextureCoord;
    std::vector<float> m_UvCoord;
    std::vector<unsigned int> m_Index={
        0,1,2,
        2,3,0
    };
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITE_HPP

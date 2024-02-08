//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP
#include "Selectable.hpp"
#include "Util/GameObject.hpp"
#include "glm/glm.hpp"

class button:public Util::GameObject{
/**
 * member click box
 * member: image
 * Click function
 * Check Cursor Click function (cursor location)
 * **/
private:
glm::vec2 ClickBoxRegionTopL;
glm::vec2 ClickBoxRegionBotmR;
glm::vec2 ObjectLocation;
public:

    button(){};
    button(glm::vec2 objectLocation,glm::vec2 RegionTopL,glm::vec2 RegionBotmR): ObjectLocation(objectLocation),ClickBoxRegionTopL(RegionTopL),ClickBoxRegionBotmR(RegionBotmR){};
    ~button(){};

    void Update(const Util::Transform &transform = Util::Transform()) override;
    void Start()override{
        ObjectLocation=glm::vec2(500,200);


    };

    bool CheckCursorClickLocation(glm::vec2 cursorLocation){
        //which is more efficent? pass data or call the cursor get location function
        float topY=ClickBoxRegionTopL.y;
        float leftX=ClickBoxRegionTopL.x;
        float botY=ClickBoxRegionBotmR.y;
        float rightX=ClickBoxRegionBotmR.x;

        if(cursorLocation.x<leftX&&cursorLocation.x>rightX&&cursorLocation.y<topY&&cursorLocation.y>botY){
            return true;
        }else{
            return false;
        }

    };

    void Click(glm::vec2 cursorLocation){
        if(CheckCursorClickLocation(cursorLocation)== true){

        }
    }


};



#endif // PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP

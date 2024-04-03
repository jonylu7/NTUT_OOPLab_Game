//
// Created by 盧威任 on 3/26/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SELECTABLE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SELECTABLE_HPP
class Selectable {
public:
    // virtual void onSelected() = 0;
    bool getSelected() { return b_Selected; }
    void setSelected(bool value) { b_Selected = value; }

protected:
    bool b_Selected;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SELECTABLE_HPP

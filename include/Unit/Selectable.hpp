//
// Created by 盧威任 on 3/26/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SELECTABLE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SELECTABLE_HPP
class Selectable {
public:
    Selectable()
        : b_Selected(false) {}

    Selectable(bool selected)
        : b_Selected(selected) {}
    virtual ~Selectable() {}
    bool getSelected() { return b_Selected; }
    void setSelected(bool value) { b_Selected = value; }
    virtual void whenSelected() = 0;

protected:
    bool b_Selected = false;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SELECTABLE_HPP

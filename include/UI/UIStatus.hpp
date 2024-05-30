//
// Created by 盧威任 on 5/25/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UISTATUS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UISTATUS_HPP
enum class UIStatusType {
    UI_PAUSED,
    UI_CONTINUE,
    UI_EXIT,
    UI_START,
    UI_RESTART,
    UI_DEFAULT
};
class UIStatus {
public:
    UIStatus(){};
    ~UIStatus(){};
    UIStatusType getUIStatusType() { return m_Type; }
    void setUIStatusType(UIStatusType type) { m_Type = type; }

private:
    UIStatusType m_Type = UIStatusType::UI_DEFAULT;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UISTATUS_HPP

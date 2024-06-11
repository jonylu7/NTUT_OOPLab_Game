//
// Created by 盧威任 on 5/2/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_AVATARORDER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_AVATARORDER_HPP
enum class AvatarOrderType { SPAWNED, OPEN_FIRE,CHASE, MOVE, NO_ORDER, TAKEN_DAMAGE };
class AvatarOrder {
public:
    AvatarOrder() {}
    virtual ~AvatarOrder() {}
    AvatarOrderType getAvatarOrder() { return m_AvatarOrder; }
    void setAvatarOrder(AvatarOrderType order) { m_AvatarOrder = order; }

protected:
    AvatarOrderType m_AvatarOrder;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_AVATARORDER_HPP

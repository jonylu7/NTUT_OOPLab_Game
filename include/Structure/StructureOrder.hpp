//
// Created by 盧威任 on 5/1/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREORDER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREORDER_HPP

class StructureOrder {

public:
    StructureOrder() {}
    virtual ~StructureOrder() {}
    enum class StructOrder {
        NOT_CONSTRUCTED_YET,
        CONSTRUCTED,
        SELECTING_SITE,
        BUILT
    };
    StructOrder getStructOrder() { return m_StructOrder; }

    void setStructOrder(StructOrder structorder) {
        m_StructOrder = structorder;
    }

    bool getBuilt() {
        if (m_StructOrder == StructOrder::BUILT) {
            return true;
        } else {
            return false;
        }
    }

protected:
    StructOrder m_StructOrder;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREORDER_HPP

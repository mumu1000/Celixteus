#ifndef PLAYERBONUS_H
#define PLAYERBONUS_H

#include <Bonus.h>


class PlayerBonus : public Bonus
{
    public:
        PlayerBonus();
        virtual ~PlayerBonus();

    protected:
        float m_miningRarityFactor=1.0f;
        float m_miningRichUpChance=1.0f;
        float m_miningRichnessBaseFactor=1.0f;
        float m_materialPriceFactor=1.0f;
        float m_mineralToCashFactor=1.0f;
        float m_cashToMineralFactor=1.0f;
        float m_shipExpFactor=1.0f;
        float m_shipStatsFactor=1.0f;
    private:
};

#endif // PLAYERBONUS_H

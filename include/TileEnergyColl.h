#ifndef TILEENERGYCOLL_H
#define TILEENERGYCOLL_H

#include "AbstractTilePlaceable.h"
class PlayerPresence;
class Tile;
class TileEnergyColl : public AbstractTilePlaceable
{
    public:
        TileEnergyColl(Tile* slot);
        virtual ~TileEnergyColl();
        virtual void update();
        bool upgrade(std::tuple<int,int,int> levels);




        bool isAffordable(std::tuple<int,int,int> levels);
        unsigned long long calculateUpgradeTime(std::tuple<int,int,int> levels);
        unsigned long long calculateCost(std::tuple<int,int,int> levels);




    protected:

        unsigned long long m_crystProduction;
        unsigned long long m_crystStored;
        unsigned long long m_maxCrystStorage;

    private:
};

#endif // TILEENERGYCOLL_H

#ifndef TILEMINER_H
#define TILEMINER_H

#include "AbstractTilePlaceable.h"

class PlayerPresence;
class Tile;
class TileMiner : public AbstractTilePlaceable
{
    public:
        TileMiner(Tile* slot);
        virtual ~TileMiner();
        virtual void update();
        bool upgrade(std::tuple<int,int,int> levels);




bool isAffordable(std::tuple<int,int,int> levels);
unsigned long long calculateUpgradeTime(std::tuple<int,int,int> levels);
unsigned long long calculateCost(std::tuple<int,int,int> levels);




    protected:

        unsigned long long getUniverseTick();
        PlayerPresence* getOwner();
        unsigned long long m_crystProduction;
        unsigned long long m_crystStored;
        unsigned long long m_maxCrystStorage;

    private:
};

#endif // TILEMINER_H

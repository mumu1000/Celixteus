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
        virtual void update(PlayerPresence* updatingPlayer);
        virtual void collect(PlayerPresence* collectingPlayer);
        bool upgrade(std::tuple<int,int,int> levels);
        virtual std::string description();


        bool isAffordable(std::tuple<int,int,int> levels);
        unsigned long long calculateUpgradeTime(std::tuple<int,int,int> levels);
        unsigned long long calculateRelUpgradeTime(std::tuple<int,int,int> levels);
        unsigned long long calculateCost(std::tuple<int,int,int> levels);
        unsigned long long calculateRelCost(std::tuple<int,int,int> levels);


        //unsigned long long getCrystProd(){return m_crystProduction;}
        //unsigned long long getCrystStored(){return m_crystStored;}
        //unsigned long long getMaxCrystStorage(){return m_maxCrystStorage;}



    protected:

        void updateTileValues();
        unsigned long long m_crystProduction=0;
        unsigned long long m_crystStored=0;
        unsigned long long m_maxCrystStorage=0;

    private:
};

#endif // TILEMINER_H

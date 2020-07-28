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
        virtual void update(PlayerPresence* updatingPlayer);
        bool upgrade(std::tuple<int,int,int> levels);
        virtual std::string description();



        bool isAffordable(std::tuple<int,int,int> levels);
        unsigned long long calculateUpgradeTime(std::tuple<int,int,int> levels);
        unsigned long long calculateCost(std::tuple<int,int,int> levels);




    protected:

        unsigned long long m_enerProduction=0;
        unsigned long long m_enerStored=0;
        unsigned long long m_maxEnerStorage=0;

    private:
};

#endif // TILEENERGYCOLL_H

#ifndef TILEORESTORAGE_H
#define TILEORESTORAGE_H

#include "AbstractTilePlaceable.h"
class PlayerPresence;
class Tile;
class TileOreStorage : public AbstractTilePlaceable
{
    public:
        TileOreStorage(Tile* slot);
        virtual ~TileOreStorage();
        virtual void update(PlayerPresence* updatingPlayer);
        virtual void collect(PlayerPresence* collectingPlayer);
        bool upgrade(std::tuple<int,int,int> levels);
        virtual std::string description();



        bool isAffordable(std::tuple<int,int,int> levels);
        unsigned long long calculateUpgradeTime(std::tuple<int,int,int> levels);
        unsigned long long calculateRelUpgradeTime(std::tuple<int,int,int> levels);
        unsigned long long calculateCost(std::tuple<int,int,int> levels);
        unsigned long long calculateRelCost(std::tuple<int,int,int> levels);





    protected:

        void updateTileValues();
        unsigned long long m_crystStorage=0;
        unsigned long long m_ackCrystStorage=0;

    private:
};

#endif // TILEORESTORAGE_H

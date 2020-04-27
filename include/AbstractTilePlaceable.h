#ifndef ABSTRACTTILEPLACEABLE_H
#define ABSTRACTTILEPLACEABLE_H
#include <tuple>

class PlayerPresence;
class Tile;
class AbstractTilePlaceable
{
    public:

        enum BuildingType { Nothing ,Miner, EnergyColl, OreStorage}; //"Nothing" is here to implement a value for the no action statement. It should not name a real building type.
        AbstractTilePlaceable(Tile* slot);
        virtual ~AbstractTilePlaceable();
        virtual void update()=0;
        BuildingType getType(){return m_type;};
        std::tuple<int,int,int> getLevels(){return m_levels;};
        virtual bool upgrade(std::tuple<int,int,int> levels)=0;
        virtual bool isAffordable(std::tuple<int,int,int> levels)=0;
        virtual unsigned long long calculateUpgradeTime(std::tuple<int,int,int> levels)=0;
        virtual unsigned long long calculateCost(std::tuple<int,int,int> levels)=0;



    protected:
        std::tuple<int,int,int> m_levels;
        BuildingType m_type;
        Tile* m_slot;
        unsigned long long m_lastTickUpdated;
        unsigned long long getUniverseTick();
        PlayerPresence* getOwner();
    private:
};

#endif // ABSTRACTTILEPLACEABLE_H

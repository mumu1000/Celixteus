#ifndef ABSTRACTTILEPLACEABLE_H
#define ABSTRACTTILEPLACEABLE_H
#include <tuple>

class Tile;
class AbstractTilePlaceable
{
    public:

        enum BuildingType { Nothing ,Miner }; //"Nothing" is here to implement a value for the no action statement. It should not name a real building type.
        AbstractTilePlaceable(Tile* slot);
        virtual ~AbstractTilePlaceable();
        virtual void update()=0;
        BuildingType getType(){return m_type;};
        std::tuple<int,int,int> getLevels(){return m_levels;};
        virtual bool upgrade(std::tuple<int,int,int> levels)=0;

    protected:
        std::tuple<int,int,int> m_levels;
        BuildingType m_type;
        Tile* m_slot;
        unsigned long long m_lastTickUpdated;
    private:
};

#endif // ABSTRACTTILEPLACEABLE_H

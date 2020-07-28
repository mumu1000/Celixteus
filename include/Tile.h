#ifndef TILE_H
#define TILE_H
#define TILE_WIDTH 100
#define TILE_HEIGHT 100
#include "AbstractTilePlaceable.h"

class PlayerPresence;
class AbstractTilePlaceable;
class Planet;
class Tile
{
    public:
        Tile(Planet* planet);
        Tile(Planet* planet, unsigned int xPos, unsigned int yPos);
        virtual ~Tile();

        void update(PlayerPresence* updatingPlayer);
        bool build(AbstractTilePlaceable::BuildingType type);
        bool upgrade(std::tuple<int,int,int> levels);

        Planet* getPlanet(){return m_planet;};

        AbstractTilePlaceable* getTileContent(){return m_tileContent;};
    protected:
        unsigned int m_xPos;
        unsigned int m_yPos;
        AbstractTilePlaceable* m_tileContent;
        Planet* m_planet;
    private:
};

#endif // TILE_H

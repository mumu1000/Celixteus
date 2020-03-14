#ifndef TILE_H
#define TILE_H
#define TILE_WIDTH 100
#define TILE_HEIGHT 100
#include <iostream>
#include "AbstractTilePlaceable.h"
#include "Player.h"

class AbstractTilePlaceable;
class Planet;
class Tile
{
    public:
        Tile(Player* owner, Planet* planet);
        Tile(Player* owner, Planet* planet, unsigned int xPos, unsigned int yPos);
        virtual ~Tile();

        enum TileType { miner, energyExtractor, storageBuilding };


        void draw(float xOrigin, float yOrigin, float zoom);
        void update();
        bool build(TileType type);
        Planet* getPlanet(){return m_planet;};
    protected:
        unsigned int m_xPos;
        unsigned int m_yPos;
        AbstractTilePlaceable* m_tileContent;
        Player* m_owner;
        Planet* m_planet;

    private:
};

#endif // TILE_H

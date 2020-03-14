#ifndef PLANET_H
#define PLANET_H
#include <vector>
#include "Tile.h"
#include <iostream>
#include "Player.h"

class Tile;
class SolarSys;
class PlanetView;
class Planet
{
    public:
        friend PlanetView;
        Planet(Player* owner, SolarSys* solarSys);
        Planet(Player* owner, SolarSys* solarSys, unsigned int planetSize);
        virtual ~Planet();
        void draw(float xOrigin, float yOrigin, float zoom);
        void update();
        Tile& operator[](unsigned int i);
        unsigned int size(){return m_tileList.size();};
        SolarSys* getSolarSys(){return m_solarSys;};


    protected:
        std::vector<Tile*> m_tileList;
        Player* m_owner;
        SolarSys* m_solarSys;
    private:
};

#endif // PLANET_H

/*
- Tile
-


*/

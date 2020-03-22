#ifndef PLANET_H
#define PLANET_H
#include <vector>
#include <iostream>

class Tile;
class SolarSys;
class PlanetView;
class PlayerPresence;
class Universe;
class Planet
{
    public:
        friend PlanetView;
        Planet(PlayerPresence* owner, SolarSys* solarSys);
        Planet(PlayerPresence* owner, SolarSys* solarSys, unsigned int planetSize);
        virtual ~Planet();
        void update();
        Universe* getUniverse();
        Tile& operator[](unsigned int i);
        unsigned int size(){return m_tileList.size();};
        SolarSys* getSolarSys(){return m_solarSys;};
        PlayerPresence* getOwner(){return m_owner;};

    protected:
        std::vector<Tile*> m_tileList;
        PlayerPresence* m_owner;
        SolarSys* m_solarSys;
    private:
};

#endif // PLANET_H



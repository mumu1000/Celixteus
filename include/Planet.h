#ifndef PLANET_H
#define PLANET_H
#include <vector>
#include <iostream>

class Tile;
class SolarSys;
class PlanetView;
class Player;
class Planet
{
    public:
        friend PlanetView;
        Planet(Player* owner, SolarSys* solarSys);
        Planet(Player* owner, SolarSys* solarSys, unsigned int planetSize);
        virtual ~Planet();
        void draw(float xOrigin, float yOrigin, float zoom);
        void update();
        Universe* getUniverse();
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



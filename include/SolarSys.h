#ifndef SOLARSYS_H
#define SOLARSYS_H
#include <vector>

class Planet;
class SolarSysView;
class Galaxy;
class Universe;
class PlayerPresence;
class SolarSys
{
    public:
        friend SolarSysView;
        SolarSys(Galaxy* galaxy);
        SolarSys(Galaxy* galaxy, unsigned int solarSysSize);
        virtual ~SolarSys();
        void genPlanet(unsigned int generatingPlayerId, unsigned int planetId);  //IDEMPOTENT FUNCTION, DOES NOTHING IF TARGET IS ALREADY GENERATED (aka vector at index not nullptr)
        void update(PlayerPresence* updatingPlayer);
        Universe* getUniverse();
        Planet& operator[](unsigned int i);
        unsigned int size(){return m_planetList.size();};
        Galaxy* getGalaxy(){return m_galaxy;};

    protected:
        std::vector<Planet*> m_planetList;
        Galaxy* m_galaxy;

    private:
};

#endif // SOLARSYS_H

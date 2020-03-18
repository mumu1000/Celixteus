#ifndef SOLARSYS_H
#define SOLARSYS_H
#include <vector>

class Planet;
class SolarSysView;
class Galaxy;
class SolarSys
{
    public:
        friend SolarSysView;
        SolarSys(Galaxy* galaxy);
        SolarSys(Galaxy* galaxy, unsigned int solarSysSize);
        virtual ~SolarSys();
        void update();
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

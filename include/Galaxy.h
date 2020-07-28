#ifndef GALAXY_H
#define GALAXY_H
#include <vector>

class SolarSys;
class GalaxyView;
class Cluster;
class Universe;
class PlayerPresence;
class Galaxy
{
    public:
        friend GalaxyView;
        Galaxy(Cluster* cluster);
        Galaxy(Cluster* cluster, unsigned int galaxySize);
        virtual ~Galaxy();
        void genSolarSys(unsigned int generatingPlayerId, unsigned int solarSysId);  //IDEMPOTENT FUNCTION, DOES NOTHING IF TARGET IS ALREADY GENERATED (aka vector at index not nullptr)
        void update(PlayerPresence* updatingPlayer);
        Universe* getUniverse();
        SolarSys& operator[](unsigned int i);
        unsigned int size(){return m_solarSysList.size();};
        Cluster* getCluster(){return m_cluster;};

    protected:
        std::vector<SolarSys*> m_solarSysList;
        Cluster* m_cluster;

    private:
};

#endif // GALAXY_H

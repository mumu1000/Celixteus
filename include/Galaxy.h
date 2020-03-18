#ifndef GALAXY_H
#define GALAXY_H
#include <vector>

class SolarSys;
class GalaxyView;
class Cluster;
class Galaxy
{
    public:
        friend GalaxyView;
        Galaxy(Cluster* cluster);
        Galaxy(Cluster* cluster, unsigned int galaxySize);
        virtual ~Galaxy();
        void update();
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

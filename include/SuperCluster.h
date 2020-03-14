#ifndef SUPERCLUSTER_H
#define SUPERCLUSTER_H
#include <vector>
#include "Cluster.h"
class Cluster;
class SuperClusterView;
class Universe;
class SuperCluster
{
    public:
        friend SuperClusterView;
        SuperCluster(Universe* universe);
        SuperCluster(Universe* universe, unsigned int SuperClusterSize);
        virtual ~SuperCluster();
        void update();
        Cluster& operator[](unsigned int i);
        unsigned int size(){return m_clusterList.size();};
        Universe* getUniverse(){return m_universe;};

    protected:
        std::vector<Cluster*> m_clusterList;
        Universe* m_universe;

    private:
};

#endif // SUPERCLUSTER_H

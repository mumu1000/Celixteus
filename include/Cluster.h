#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include "Galaxy.h"

class Galaxy;
class ClusterView;
class SuperCluster;
class Cluster
{
    public:
        friend ClusterView;
        Cluster(SuperCluster* superCluster);
        Cluster(SuperCluster* superCluster, unsigned int clusterSize);
        virtual ~Cluster();
        void update();
        Galaxy& operator[](unsigned int i);
        unsigned int size(){return m_galaxyList.size();};
        SuperCluster* getSuperCluster(){return m_superCluster;};

    protected:
        std::vector<Galaxy*> m_galaxyList;
        SuperCluster* m_superCluster;

    private:
};

#endif // CLUSTER_H

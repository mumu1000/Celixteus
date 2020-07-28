#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>

class Galaxy;
class ClusterView;
class SuperCluster;
class Universe;
class PlayerPresence;
class Cluster
{
    public:
        friend ClusterView;
        Cluster(SuperCluster* superCluster);
        Cluster(SuperCluster* superCluster, unsigned int clusterSize);
        virtual ~Cluster();
        void genGalaxy(unsigned int generatingPlayerId, unsigned int galaxyId);  //IDEMPOTENT FUNCTION, DOES NOTHING IF TARGET IS ALREADY GENERATED (aka vector at index not nullptr)
        void update(PlayerPresence* updatingPlayer);
        Galaxy& operator[](unsigned int i);
        unsigned int size(){return m_galaxyList.size();};
        Universe* getUniverse();
        SuperCluster* getSuperCluster(){return m_superCluster;};

    protected:
        std::vector<Galaxy*> m_galaxyList;
        SuperCluster* m_superCluster;

    private:
};

#endif // CLUSTER_H

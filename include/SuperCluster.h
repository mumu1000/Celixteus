#ifndef SUPERCLUSTER_H
#define SUPERCLUSTER_H
#include <vector>
class Cluster;
class SuperClusterView;
class Universe;
class PlayerPresence;
class SuperCluster
{
    public:
        friend SuperClusterView;
        SuperCluster(Universe* universe);
        SuperCluster(Universe* universe, unsigned int SuperClusterSize);
        void genCluster(unsigned int generatingPlayerId, unsigned int clusterId);  //IDEMPOTENT FUNCTION, DOES NOTHING IF TARGET IS ALREADY GENERATED (aka vector at index not nullptr)
        virtual ~SuperCluster();
        void update(PlayerPresence* updatingPlayer);
        Cluster& operator[](unsigned int i);
        unsigned int size(){return m_clusterList.size();};
        Universe* getUniverse(){return m_universe;};

    protected:
        std::vector<Cluster*> m_clusterList;
        Universe* m_universe;

    private:
};

#endif // SUPERCLUSTER_H

#include "SuperCluster.h"
#include "Cluster.h"
#include "Universe.h"
#include <iostream>

//THERE IS STILL SOME SHITTY CONSTANT HERE COMON

SuperCluster::SuperCluster(Universe* universe)
{
    m_universe = universe;
}

SuperCluster::SuperCluster(Universe* universe, unsigned int superClusterSize)
{
    m_universe = universe;
    m_clusterList.reserve( superClusterSize );
    for (unsigned int x = 0; x != superClusterSize ; x++)
    {
        m_clusterList.push_back(nullptr);
    }
    std::cout << "Création d'un SuperCluster contenant " << (m_clusterList.size()) << " Cluster terminée\n";
}

SuperCluster::~SuperCluster()
{

}

void SuperCluster::genCluster(unsigned int generatingPlayerId, unsigned int clusterId)
{
    if ((clusterId<m_clusterList.size()) && (m_clusterList[clusterId] == nullptr))
    {
        m_clusterList[clusterId] = new Cluster(this,5);
    }
}

void SuperCluster::update()
{
    for (unsigned int i = 0; i != m_clusterList.size() ;i++ )
    {
        if (m_clusterList[i] != nullptr)
        {
            m_clusterList[i]->update();
        }
    }
}

Cluster& SuperCluster::operator[](unsigned int i)
{
    return *m_clusterList[i];
}

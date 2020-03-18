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
        std::cout << "Cluster numero " << (x+1) << " sur " << superClusterSize << " créé\n";
        m_clusterList.push_back(new Cluster(this, 5));
    }
    std::cout << "Création d'un SuperCluster contenant " << (m_clusterList.size()) << " Cluster terminée\n";
}

SuperCluster::~SuperCluster()
{

}


void SuperCluster::update()
{
    for (unsigned int i = 0; i != m_clusterList.size() ;i++ )
    {
        m_clusterList[i]->update();
    }
}

Cluster& SuperCluster::operator[](unsigned int i)
{
    return *m_clusterList[i];
}

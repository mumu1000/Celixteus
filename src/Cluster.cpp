#include "Cluster.h"

//THERE IS STILL SOME SHITTY CONSTANT HERE COMON

Cluster::Cluster(SuperCluster* superCluster)
{
    m_superCluster = superCluster;
}

Cluster::Cluster(SuperCluster* superCluster, unsigned int clusterSize)
{
    m_superCluster = superCluster;
    m_galaxyList.reserve( clusterSize );
    for (unsigned int x = 0; x != clusterSize ; x++)
    {
        std::cout << "Galaxy numero " << (x+1) << " sur " << clusterSize << " créée\n";
        m_galaxyList.push_back(new Galaxy(this, 5));
    }
    std::cout << "Création d'un Cluster contenant " << (m_galaxyList.size()) << " Galaxy terminée\n";
}

Cluster::~Cluster()
{

}


void Cluster::update()
{
    for (unsigned int i = 0; i != m_galaxyList.size() ;i++ )
    {
        m_galaxyList[i]->update();
    }
}

Galaxy& Cluster::operator[](unsigned int i)
{
    return *m_galaxyList[i];
}

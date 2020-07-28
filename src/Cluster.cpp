#include "Cluster.h"
#include "Galaxy.h"
#include "SuperCluster.h"
#include "Universe.h"
#include <iostream>
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
        m_galaxyList.push_back(nullptr);
    }
    std::cout << "Création d'un Cluster contenant " << (m_galaxyList.size()) << " Galaxy terminée\n";
}

Cluster::~Cluster()
{

}

void Cluster::genGalaxy(unsigned int generatingPlayerId, unsigned int galaxyId)
{
    if ((galaxyId<m_galaxyList.size()) && (m_galaxyList[galaxyId] == nullptr))
    {
        m_galaxyList[galaxyId] = new Galaxy(this,5);
    }
}

Universe* Cluster::getUniverse()
{
    return m_superCluster->getUniverse();
}
void Cluster::update(PlayerPresence* updatingPlayer)
{
    for (unsigned int i = 0; i != m_galaxyList.size() ;i++ )
    {
        if (m_galaxyList[i] != nullptr)
        {
            m_galaxyList[i]->update(updatingPlayer);
        }
    }
}

Galaxy& Cluster::operator[](unsigned int i)
{
    return *m_galaxyList[i];
}

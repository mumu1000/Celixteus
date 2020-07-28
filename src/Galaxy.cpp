#include "Galaxy.h"
#include "SolarSys.h"
#include "Cluster.h"
#include "Universe.h"
#include <iostream>

//THERE IS STILL SOME SHITTY CONSTANT HERE COMON

Galaxy::Galaxy(Cluster* cluster)
{
    m_cluster = cluster;
}

Galaxy::Galaxy(Cluster* cluster,unsigned int galaxySize)
{
    m_cluster = cluster;
    m_solarSysList.reserve( galaxySize );
    for (unsigned int x = 0; x != galaxySize ; x++)
    {
        m_solarSysList.push_back(nullptr);
    }
    std::cout << "Création d'une Galaxy contenant " << (m_solarSysList.size()) << " SolarSys terminée\n";
}

Galaxy::~Galaxy()
{

}

void Galaxy::genSolarSys(unsigned int generatingPlayerId, unsigned int solarSysId)
{
    if ((solarSysId<m_solarSysList.size()) && (m_solarSysList[solarSysId] == nullptr))
    {
        m_solarSysList[solarSysId] = new SolarSys(this,5);
    }
}

Universe* Galaxy::getUniverse()
{
    return m_cluster->getUniverse();
}

void Galaxy::update(PlayerPresence* updatingPlayer)
{
    for (unsigned int i = 0; i != m_solarSysList.size() ;i++ )
    {
        if (m_solarSysList[i] != nullptr)
        {
            m_solarSysList[i]->update(updatingPlayer);
        }
    }
}

SolarSys& Galaxy::operator[](unsigned int i)
{
    return *m_solarSysList[i];
}

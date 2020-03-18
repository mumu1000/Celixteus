#include "Galaxy.h"
#include "SolarSys.h"
#include "Cluster.h"
#include "Universe.h"

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
        std::cout << "SolarSys numero " << (x+1) << " sur " << galaxySize << " créée\n";
        m_solarSysList.push_back(new SolarSys(this , 5));
    }
    std::cout << "Création d'une Galaxy contenant " << (m_solarSysList.size()) << " SolarSys terminée\n";
}

Galaxy::~Galaxy()
{

}

Universe* Galaxy::getUniverse()
{
    return m_cluster->getUniverse();
}

void Galaxy::update()
{
    for (unsigned int i = 0; i != m_solarSysList.size() ;i++ )
    {
        m_solarSysList[i]->update();
    }
}

SolarSys& Galaxy::operator[](unsigned int i)
{
    return *m_solarSysList[i];
}

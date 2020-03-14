#include "SolarSys.h"
//THERE IS STILL SOME SHITTY CONSTANT HERE COMON

SolarSys::SolarSys(Galaxy* galaxy)
{
    m_galaxy = galaxy;
}

SolarSys::SolarSys(Galaxy* galaxy, unsigned int solarSysSize)
{
    m_galaxy = galaxy;
    m_planetList.reserve( solarSysSize );
    for (unsigned int x = 0; x != solarSysSize ; x++)
    {
        std::cout << "Planet numero " << (x+1) << " sur " << solarSysSize << " créée\n";
        m_planetList.push_back(new Planet(nullptr,this, 5));
    }
    std::cout << "Création d'un SolarSys contenant " << (m_planetList.size()) << " Planet terminée\n";
}

SolarSys::~SolarSys()
{

}

void SolarSys::update()
{
    for (unsigned int i = 0; i != m_planetList.size() ;i++ )
    {
        m_planetList[i]->update();
    }
}

Planet& SolarSys::operator[](unsigned int i)
{
    return *m_planetList[i];
}

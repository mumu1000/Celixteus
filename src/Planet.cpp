#include "Planet.h"
#include "Tile.h"
#include "SolarSys.h"
#include "Universe.h"
#include "Player.h"

Planet::Planet(PlayerPresence* owner, SolarSys* solarSys)
{
    m_owner = owner;
    m_solarSys = solarSys;
}

Planet::Planet(PlayerPresence* owner, SolarSys* solarSys, unsigned int planetSize)
{
    m_owner = owner;
    m_solarSys = solarSys;
    m_tileList.reserve( planetSize*planetSize );
    for (unsigned int x = 0; x != planetSize ; x++)
    {
        for (unsigned int y = 0; y != planetSize ; y++)
        {
            m_tileList.push_back(new Tile(this,x,y));
        }
    }


}

Planet::~Planet()
{
    std::cout << "Planet Detruite\n";
}



Universe* Planet::getUniverse()
{
    return m_solarSys->getUniverse();
}

void Planet::update()
{
    for (unsigned int i = 0; i != m_tileList.size() ;i++ )
    {
        if (m_tileList[i] != nullptr)
        {
            m_tileList[i]->update();
        }
    }
}

Tile& Planet::operator[](unsigned int i)
{
    return *m_tileList[i];
}

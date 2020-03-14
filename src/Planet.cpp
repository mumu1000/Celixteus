#include "Planet.h"

Planet::Planet(Player* owner, SolarSys* solarSys)
{
    m_owner = owner;
    m_solarSys = solarSys;
}

Planet::Planet(Player* owner, SolarSys* solarSys, unsigned int planetSize)
{
    m_owner = owner;
    m_solarSys = solarSys;
    m_tileList.reserve( planetSize*planetSize );
    for (unsigned int x = 0; x != planetSize ; x++)
    {
        for (unsigned int y = 0; y != planetSize ; y++)
        {
            std::cout << "Tile numero " << (x*planetSize+y+1) << " sur " << (planetSize*planetSize) << " créée\n";
            m_tileList.push_back(new Tile(m_owner,this,x,y));
        }
    }


}

Planet::~Planet()
{
    std::cout << "Planet Detruite\n";
}

void Planet::draw(float xOrigin, float yOrigin, float zoom)
{
    std::cout << "Je suis en train de dessiner une planete\n";
    for (unsigned int i = 0; i != m_tileList.size() ;i++ )
    {
        m_tileList[i]->draw(xOrigin, yOrigin, zoom);
    }
}

void Planet::update()
{
    for (unsigned int i = 0; i != m_tileList.size() ;i++ )
    {
        m_tileList[i]->update();
    }
}

Tile& Planet::operator[](unsigned int i)
{
    return *m_tileList[i];
}

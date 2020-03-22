#include "Tile.h"
#include "TileMiner.h"
#include <iostream>
Tile::Tile(Planet* planet)
{
    m_planet = planet;
    m_xPos = 0;
    m_yPos = 0;
    m_tileContent = nullptr;
}

Tile::Tile(Planet* planet, unsigned int xPos, unsigned int yPos)
{
    m_planet = planet;
    m_xPos = xPos;
    m_yPos = yPos;
    m_tileContent = nullptr;
}

Tile::~Tile()
{
    //dtor
}

bool Tile::build(AbstractTilePlaceable::BuildingType type)
{
    if (m_tileContent != nullptr) {return false;}
    switch(type)
    {
        case AbstractTilePlaceable::Miner : m_tileContent = new TileMiner(this);return true;break;
        default : std::cout << "Tumfaisconstruirenimp\n";return false;break;
    }
}

bool Tile::upgrade(std::tuple<int,int,int> levels)
{
    if (m_tileContent == nullptr) {return false;}
    return m_tileContent->upgrade(levels);
}

void Tile::update()
{
    if (m_tileContent != nullptr)
    {
        m_tileContent->update();
    }
}

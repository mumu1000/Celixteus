#include "Tile.h"
#include "TileMiner.h"
Tile::Tile(PlayerPresence* owner, Planet* planet)
{
    m_owner = owner;
    m_planet = planet;
    m_xPos = 0;
    m_yPos = 0;
    m_tileContent = nullptr;
}

Tile::Tile(PlayerPresence* owner, Planet* planet, unsigned int xPos, unsigned int yPos)
{
    m_owner = owner;
    m_planet = planet;
    m_xPos = xPos;
    m_yPos = yPos;
    m_tileContent = nullptr;
}

Tile::~Tile()
{
    //dtor
}

bool Tile::build(Tile::TileType type)
{
    switch(type)
    {
        case Tile::miner    : m_tileContent = new TileMiner(this);return true;break;
        default             : std::cout << "Tumfaisconstruirenimp\n";return false;break ;
    }
}

void Tile::draw(float xOrigin, float yOrigin, float zoom)
{
    std::cout << "Je suis en train de dessinner une Tile en position x=" << m_xPos << " et y= " << m_yPos << "\n";
    if (m_tileContent != nullptr)
    {
        m_tileContent->draw(xOrigin, yOrigin, zoom, m_xPos, m_yPos);
    }
}

void Tile::update()
{
    if (m_tileContent != nullptr)
    {
        m_tileContent->update();
    }
}

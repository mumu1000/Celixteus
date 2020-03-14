#include "TileMiner.h"
#include "Tile.h"

TileMiner::TileMiner(Tile* slot) : AbstractTilePlaceable(slot)
{
}

TileMiner::~TileMiner()
{
    //dtor
}

void TileMiner::draw(float xOrigin, float yOrigin, float zoom, unsigned int xPos, unsigned int yPos)
{
    unsigned long long universeTime = m_slot->getPlanet()->getSolarSys()->getGalaxy()->getCluster()->getSuperCluster()->getUniverse()->getUniverseTick();
    std::cout << "A TileMiner is getting drawn: it has last been updated at tick number " << m_lastTickUpdated << " thus is " << (universeTime - m_lastTickUpdated) << " tick late of the Universe time\n";
}

void TileMiner::update()
{

}

#include "AbstractTilePlaceable.h"

AbstractTilePlaceable::AbstractTilePlaceable(Tile* slot)
{
    m_slot = slot;
    m_lastTickUpdated = slot->getPlanet()->getSolarSys()->getGalaxy()->getCluster()->getSuperCluster()->getUniverse()->getUniverseTick();
}

AbstractTilePlaceable::~AbstractTilePlaceable()
{
    //dtor
}

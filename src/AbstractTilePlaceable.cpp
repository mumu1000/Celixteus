#include "AbstractTilePlaceable.h"
#include "Tile.h"
#include "Planet.h"
#include "Universe.h"

AbstractTilePlaceable::AbstractTilePlaceable(Tile* slot)
{
    m_slot = slot;
    m_lastTickUpdated = slot->getPlanet()->getUniverse()->getUniverseTick();
}

AbstractTilePlaceable::~AbstractTilePlaceable()
{
    //dtor
}

PlayerPresence* AbstractTilePlaceable::getOwner()
{
    return m_slot->getPlanet()->getOwner();
}

unsigned long long AbstractTilePlaceable::getUniverseTick()
{
    return m_slot->getPlanet()->getUniverse()->getUniverseTick();
}

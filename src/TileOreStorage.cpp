#include "TileOreStorage.h"
#include "Tile.h"
#include "Planet.h"
#include "Universe.h"
#include "PlayerPresence.h"
#include <tuple>

TileOreStorage::TileOreStorage(Tile* slot) : AbstractTilePlaceable(slot)
{
    m_levels = std::make_tuple(1,0,0);
    m_type = AbstractTilePlaceable::OreStorage;
}

TileOreStorage::~TileOreStorage()
{
    //dtor
}


void TileOreStorage::update()
{
    if (m_lastTickUpdated >= getUniverseTick()) {return;}
    //UPDATE ACTIONS HERE
    m_lastTickUpdated = getUniverseTick();

}


bool TileOreStorage::upgrade(std::tuple<int,int,int> levels)
{
    if (isAffordable(levels) && getOwner()->subCredits(calculateCost(levels)) )
    {
        m_lastTickUpdated += calculateUpgradeTime(levels);
        std::get<0>(m_levels) += std::get<0>(levels);
        std::get<1>(m_levels) += std::get<1>(levels);
        std::get<2>(m_levels) += std::get<2>(levels);
        return true;
    }
    return false;
}

unsigned long long TileOreStorage::calculateCost(std::tuple<int,int,int> levels)
{
    return 0;
}

unsigned long long TileOreStorage::calculateUpgradeTime(std::tuple<int,int,int> levels)
{
    return 0;
}

bool TileOreStorage::isAffordable(std::tuple<int,int,int> levels)
{
    if (m_slot->getPlanet()->getOwner()->getCredits() >= calculateCost(levels))
    {
        return true;
    }
    return false;
}

#include "TileMiner.h"
#include "Tile.h"
#include "Planet.h"
#include "Universe.h"
#include "PlayerPresence.h"
#include <tuple>

TileMiner::TileMiner(Tile* slot) : AbstractTilePlaceable(slot)
{
    m_levels = std::make_tuple(1,1,0);
    m_type = AbstractTilePlaceable::Miner;
}

TileMiner::~TileMiner()
{
    //dtor
}


void TileMiner::update()
{
    if (m_lastTickUpdated >= getUniverseTick()) {return;}
    //UPDATE ACTIONS HERE
    m_lastTickUpdated = getUniverseTick();

}


bool TileMiner::upgrade(std::tuple<int,int,int> levels)
{
    if (isAffordable(levels) && getOwner()->subCredits(calculateCost(levels)) )
    {
        m_lastTickUpdated += calculateUpgradeTime(levels);
        std::get<0>(m_levels) += std::get<0>(levels);
        std::get<1>(m_levels) += std::get<1>(levels);
        std::get<2>(m_levels) += std::get<2>(levels);

    }
}

unsigned long long TileMiner::calculateCost(std::tuple<int,int,int> levels)
{
    return 0;
}

unsigned long long TileMiner::calculateUpgradeTime(std::tuple<int,int,int> levels)
{
    return 0;
}

bool TileMiner::isAffordable(std::tuple<int,int,int> levels)
{
    if (m_slot->getPlanet()->getOwner()->getCredits() >= calculateCost(levels))
    {
        return true;
    }
    return false;
}

PlayerPresence* TileMiner::getOwner()
{
    return m_slot->getPlanet()->getOwner();
}

unsigned long long TileMiner::getUniverseTick()
{
    return m_slot->getPlanet()->getUniverse()->getUniverseTick();
}







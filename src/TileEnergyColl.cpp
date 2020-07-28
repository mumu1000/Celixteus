#include "TileEnergyColl.h"
#include "Tile.h"
#include "Planet.h"
#include "Universe.h"
#include "PlayerPresence.h"
#include <tuple>

TileEnergyColl::TileEnergyColl(Tile* slot) : AbstractTilePlaceable(slot)
{
    m_levels = std::make_tuple(1,1,0);
    m_type = AbstractTilePlaceable::EnergyColl;
}

TileEnergyColl::~TileEnergyColl()
{
    //dtor
}


void TileEnergyColl::update(PlayerPresence* updatingPlayer)
{
    if (updatingPlayer == getOwner())
    {
        unsigned long long currtick = getUniverseTick();
        if (m_lastTickUpdated >= currtick) {return;}
        //UPDATE ACTIONS HERE
        unsigned long long tickDiff = currtick - m_lastTickUpdated;
        m_enerStored = m_enerStored + m_enerProduction*tickDiff;
        if (m_enerStored > m_maxEnerStorage) {m_enerStored = m_maxEnerStorage;}

        //END OF UPDATE ACTIONS
        m_lastTickUpdated = currtick;
    }
}


bool TileEnergyColl::upgrade(std::tuple<int,int,int> levels)
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

unsigned long long TileEnergyColl::calculateCost(std::tuple<int,int,int> levels)
{
    return 0;
}

unsigned long long TileEnergyColl::calculateUpgradeTime(std::tuple<int,int,int> levels)
{
    return 0;
}

bool TileEnergyColl::isAffordable(std::tuple<int,int,int> levels)
{
    if (m_slot->getPlanet()->getOwner()->getCredits() >= calculateCost(levels))
    {
        return true;
    }
    return false;
}

std::string TileEnergyColl::description()
{
    std::string toReturn( "Energy Collector Level " + std::to_string(std::get<0>(m_levels)) +":"+
                                                      std::to_string(std::get<1>(m_levels)) +":"+
                                                      std::to_string(std::get<2>(m_levels)) +"  "+
                                                      std::to_string(m_enerStored)         +"/"+
                                                      std::to_string(m_maxEnerStorage)     +" Energy Stored (+ "+
                                                      std::to_string(m_enerProduction)     + " / Tick)" );
    return toReturn;
}




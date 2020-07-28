#include "TileOreStorage.h"
#include "Tile.h"
#include "Planet.h"
#include "Universe.h"
#include "PlayerPresence.h"
#include <tuple>
#include <cmath>

TileOreStorage::TileOreStorage(Tile* slot) : AbstractTilePlaceable(slot)
{
    m_levels = std::make_tuple(1,0,0);
    m_type = AbstractTilePlaceable::OreStorage;
    updateTileValues();
}

TileOreStorage::~TileOreStorage()
{
    //dtor
}


void TileOreStorage::update(PlayerPresence* updatingPlayer)
{
    if (updatingPlayer == getOwner())
    {
        unsigned long long currtick = getUniverseTick();
        if (m_lastTickUpdated >= currtick) {return;}
        //UPDATE ACTIONS HERE
        if (m_ackCrystStorage < m_crystStorage)
        {
            getOwner()->addMineralCap(m_crystStorage-m_ackCrystStorage);
            m_ackCrystStorage = m_crystStorage;
        }
        m_lastTickUpdated = currtick;
    }
}


void TileOreStorage::collect(PlayerPresence* collectingPlayer)
{
    if (collectingPlayer == getOwner())
    {
        update(collectingPlayer);
    }
}

bool TileOreStorage::upgrade(std::tuple<int,int,int> levels)
{


    if (isAffordable(levels) && getOwner()->subCredits(calculateRelCost(levels)) )
    {
        m_lastTickUpdated += calculateUpgradeTime(levels);
        std::get<0>(m_levels) += std::get<0>(levels);
        std::get<1>(m_levels) += std::get<1>(levels);
        std::get<2>(m_levels) += std::get<2>(levels);
        updateTileValues();
        return true;
    }
    return false;
}

unsigned long long TileOreStorage::calculateCost(std::tuple<int,int,int> levels)
{
    return (pow(std::get<0>(levels),2)) + (pow(std::get<1>(levels),2)) + (pow(std::get<2>(levels),3));
}

unsigned long long TileOreStorage::calculateRelCost(std::tuple<int,int,int> levels)
{
    std::tuple<int,int,int> reachedLevel = std::make_tuple(std::get<0>(m_levels) + std::get<0>(levels),
                                                           std::get<1>(m_levels) + std::get<1>(levels),
                                                           std::get<2>(m_levels) + std::get<2>(levels));
    return calculateCost(reachedLevel) - calculateCost(m_levels);
}


unsigned long long TileOreStorage::calculateUpgradeTime(std::tuple<int,int,int> levels)
{
    return (std::get<0>(levels)*2) + (std::get<1>(levels)*2) + (std::get<2>(levels)*3);
}

unsigned long long TileOreStorage::calculateRelUpgradeTime(std::tuple<int,int,int> levels)
{
    std::tuple<int,int,int> reachedLevel = std::make_tuple(std::get<0>(m_levels) + std::get<0>(levels),
                                                           std::get<1>(m_levels) + std::get<1>(levels),
                                                           std::get<2>(m_levels) + std::get<2>(levels));
    return calculateUpgradeTime(reachedLevel) - calculateUpgradeTime(m_levels);;
}

bool TileOreStorage::isAffordable(std::tuple<int,int,int> levels)
{
    if (m_slot->getPlanet()->getOwner()->getCredits() >= calculateRelCost(levels))
    {
        return true;
    }
    return false;
}

void TileOreStorage::updateTileValues()
{
    m_crystStorage = ((pow(std::get<0>(m_levels),3))*10);
}


std::string TileOreStorage::description()
{
    std::string toReturn( "Ore Storage Building Level " + std::to_string(std::get<0>(m_levels)) +":"+
                                                   std::to_string(std::get<1>(m_levels)) +":"+
                                                   std::to_string(std::get<2>(m_levels)) +"  "+
                                                   std::to_string(m_crystStorage)     +" Crystal Capacity" );
    return toReturn;
}




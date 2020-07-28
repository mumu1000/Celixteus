#include "TileMiner.h"
#include "Tile.h"
#include "Planet.h"
#include "Universe.h"
#include "PlayerPresence.h"
#include <tuple>
#include <cmath>

TileMiner::TileMiner(Tile* slot) : AbstractTilePlaceable(slot)
{
    m_levels = std::make_tuple(1,1,0);
    m_type = AbstractTilePlaceable::Miner;
    updateTileValues();
}

TileMiner::~TileMiner()
{
    //dtor
}


void TileMiner::update(PlayerPresence* updatingPlayer)
{
    if (updatingPlayer == getOwner())
    {
        unsigned long long currtick = getUniverseTick();
        if (m_lastTickUpdated >= currtick) {return;}
        //UPDATE ACTIONS HERE
        unsigned long long tickDiff = currtick - m_lastTickUpdated;
        m_crystStored = m_crystStored + m_crystProduction*tickDiff;
        if (m_crystStored > m_maxCrystStorage) {m_crystStored = m_maxCrystStorage;}

        //END OF UPDATE ACTIONS
        m_lastTickUpdated = currtick;
    }
}


void TileMiner::collect(PlayerPresence* collectingPlayer)
{
    if (collectingPlayer == getOwner())
    {
        update(collectingPlayer);
        unsigned long long toBeAdded = std::min((getOwner()->getMineralCap())-(getOwner()->getMinerals()),m_crystStored);
        getOwner()->addMinerals(toBeAdded);
        m_crystStored = m_crystStored - toBeAdded;
    }
}


bool TileMiner::upgrade(std::tuple<int,int,int> levels)
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

unsigned long long TileMiner::calculateCost(std::tuple<int,int,int> levels)
{
    return (pow(std::get<0>(levels),2)) + (pow(std::get<1>(levels),2)) + (pow(std::get<2>(levels),3));
}

unsigned long long TileMiner::calculateRelCost(std::tuple<int,int,int> levels)
{
    std::tuple<int,int,int> reachedLevel = std::make_tuple(std::get<0>(m_levels) + std::get<0>(levels),
                                                           std::get<1>(m_levels) + std::get<1>(levels),
                                                           std::get<2>(m_levels) + std::get<2>(levels));
    return calculateCost(reachedLevel) - calculateCost(m_levels);
}


unsigned long long TileMiner::calculateUpgradeTime(std::tuple<int,int,int> levels)
{
    return (std::get<0>(levels)*2) + (std::get<1>(levels)*2) + (std::get<2>(levels)*3);
}

unsigned long long TileMiner::calculateRelUpgradeTime(std::tuple<int,int,int> levels)
{
    std::tuple<int,int,int> reachedLevel = std::make_tuple(std::get<0>(m_levels) + std::get<0>(levels),
                                                           std::get<1>(m_levels) + std::get<1>(levels),
                                                           std::get<2>(m_levels) + std::get<2>(levels));
    return calculateUpgradeTime(reachedLevel) - calculateUpgradeTime(m_levels);;
}

bool TileMiner::isAffordable(std::tuple<int,int,int> levels)
{
    if (m_slot->getPlanet()->getOwner()->getCredits() >= calculateRelCost(levels))
    {
        return true;
    }
    return false;
}

void TileMiner::updateTileValues()
{
    m_crystProduction = ((pow(std::get<0>(m_levels),2))*2);
    m_maxCrystStorage = ((pow(std::get<1>(m_levels),3))*10);
}

std::string TileMiner::description()
{
    std::string toReturn( "Crystal Miner Level " + std::to_string(std::get<0>(m_levels)) +":"+
                                                   std::to_string(std::get<1>(m_levels)) +":"+
                                                   std::to_string(std::get<2>(m_levels)) +"  "+
                                                   std::to_string(m_crystStored)         +"/"+
                                                   std::to_string(m_maxCrystStorage)     +" Crystals Stored (+ "+
                                                   std::to_string(m_crystProduction)     + " / Tick)" );
    return toReturn;
}





#include "PlayerPresence.h"

PlayerPresence::PlayerPresence()
{
    m_pickaxe = 0;
    m_minerals = 15;
    m_mineralCap = 50;
    m_energy = 100;
}

PlayerPresence::~PlayerPresence()
{
    //dtor
}

void PlayerPresence::addMinerals(unsigned long long toBeAdded)
{
    if (m_minerals+toBeAdded < m_minerals){m_minerals = (((unsigned long long)0)-(unsigned long long)1);} else {m_minerals += toBeAdded;}
    if (m_minerals > m_mineralCap) {m_minerals = m_mineralCap;}
}

void PlayerPresence::setMinerals(unsigned long long toBeSet)
{
    m_minerals = toBeSet;
    if (m_minerals > m_mineralCap) {m_minerals = m_mineralCap;}
}

bool PlayerPresence::subMinerals(unsigned long long toBeSubbed)
{
    if (toBeSubbed > m_minerals) {return false;}
    m_minerals -= toBeSubbed;
    return true;
}

void PlayerPresence::addMineralCap(unsigned long long toBeAdded)
{
    if (m_mineralCap+toBeAdded < m_mineralCap){m_mineralCap = (((unsigned long long)0)-(unsigned long long)1);} else {m_mineralCap += toBeAdded;}
}

void PlayerPresence::setMineralCap(unsigned long long toBeSet)
{
    m_mineralCap = toBeSet;
}

bool PlayerPresence::subMineralCap(unsigned long long toBeSubbed)
{
    if (toBeSubbed > m_mineralCap) {return false;}
    m_mineralCap -= toBeSubbed;
    return true;
}

void PlayerPresence::addEnergy(unsigned long long toBeAdded)
{
    if (m_energy+toBeAdded < m_energy){m_energy = (((unsigned long long)0)-(unsigned long long)1);} else {m_energy += toBeAdded;}

}

void PlayerPresence::setEnergy(unsigned long long toBeSet)
{
    m_energy = toBeSet;
}

bool PlayerPresence::subEnergy(unsigned long long toBeSubbed)
{
    if (toBeSubbed > m_energy) {return false;}
    m_energy -= toBeSubbed;
    return true;
}

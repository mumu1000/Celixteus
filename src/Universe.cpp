#include "Universe.h"
#include "Player.h"
#include "PlayerPresence.h"
#include "Existence.h"
#include "SuperCluster.h"
#include <iostream>

//THERE IS STILL SOME SHITTY CONSTANT HERE COMON

Universe::Universe(Existence* existence)
{
    m_existence = existence;
    m_universeTick = 0;
}

Universe::Universe(Existence* existence, unsigned int universeSize)
{
    m_existence = existence;
    m_universeTick = 0;
    m_superClusterList.reserve( universeSize );
    for (unsigned int x = 0; x != universeSize ; x++)
    {
        m_superClusterList.push_back(nullptr);
    }
    std::cout << "Création d'un Universe contenant " << (m_superClusterList.size()) << " SuperCluster terminée\n";
}

Universe::~Universe()
{

}

void Universe::genSuperCluster(unsigned int generatingPlayerId, unsigned int sClusterId)
{
    if ((sClusterId<m_superClusterList.size()) && (m_superClusterList[sClusterId] == nullptr))
    {
        m_superClusterList[sClusterId] = new SuperCluster(this,5);
    }
}


PlayerPresence* Universe::getPlayerPresOfId(unsigned int id) //Player Presence registration occurs only when a call to this function is made with an unregistered player.
{
    if (id>=m_existence->size()) {return nullptr;}

    unsigned int diff = m_existence->size() - m_playerPresenceList.size();
    m_playerPresenceList.reserve(diff);
    for (unsigned int i = 0; i<diff;i++) {m_playerPresenceList.push_back(nullptr);}
    if (m_playerPresenceList[id] == nullptr)
    {
        m_playerPresenceList[id] = new PlayerPresence();
        m_existence->getPlayerAtId(id)->registerPlayerPresence(m_playerPresenceList[id]);
    }
    return m_playerPresenceList[id];
}


void Universe::update()
{
    for (unsigned int i = 0; i != m_superClusterList.size() ;i++ )
    {
        m_superClusterList[i]->update();
    }
}

SuperCluster& Universe::operator[](unsigned int i)
{
    return *m_superClusterList[i];
}

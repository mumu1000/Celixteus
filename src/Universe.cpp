#include "Universe.h"
#include "Player.h"
#include "PlayerPresence.h"
#include "Existence.h"
#include "SuperCluster.h"
#include <iostream>
#include <chrono>
#include "allegro5/allegro.h"
//THERE IS STILL SOME SHITTY CONSTANT HERE COMON
bool Universe::clockStarted = false;

std::atomic<unsigned long long> Universe::universeTick{0};

void Universe::startTimer()
{
    if (!clockStarted)
    {
        clockStarted = true;

        std::cout << "Galaxy Global Clock Started\n";
        al_run_detached_thread(
                                [](void* clock) -> void*
                                {
                                    std::atomic<unsigned long long>* generalClock = (std::atomic<unsigned long long>*)clock;
                                    while(true)
                                    {
                                        (*generalClock) = std::chrono::system_clock::now().time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
                                        al_rest(1.0);
                                        std::cout << "clock updated to " << (*generalClock) << "\n";
                                    }
                                    return nullptr;
                                },
                                &universeTick
                               );
    }
}
Universe::Universe(Existence* existence)
{
    m_existence = existence;
    if (!clockStarted)
    {
        startTimer();
    }
}

Universe::Universe(Existence* existence, unsigned int universeSize)
{
    m_existence = existence;
    if (!clockStarted)
    {
        startTimer();
    }
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
        if (m_superClusterList[i] != nullptr)
        {
            m_superClusterList[i]->update();
        }
    }
}

SuperCluster& Universe::operator[](unsigned int i)
{
    return *m_superClusterList[i];
}

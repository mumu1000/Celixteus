#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <atomic>
class PlayerPresence;
class SuperCluster;
class UniverseView;
class Existence;
class Universe
{
    public:
        friend UniverseView;
        Universe(Existence* existence);
        Universe(Existence* existence, unsigned int universeSize);
        virtual ~Universe();
        void genSuperCluster(unsigned int generatingPlayerId, unsigned int sClusterId);  //IDEMPOTENT FUNCTION, DOES NOTHING IF TARGET IS ALREADY GENERATED (aka vector at index not nullptr)
        void update(unsigned int updatingPlayerId);
        PlayerPresence* getPlayerPresOfId(unsigned int id);
        SuperCluster& operator[](unsigned int i);
        unsigned int size(){return m_superClusterList.size();};
        unsigned long long getUniverseTick() const {return universeTick;};
        Existence* getExistence(){return m_existence;};


    protected:
        std::vector<SuperCluster*> m_superClusterList;
        std::vector<PlayerPresence*> m_playerPresenceList;
        Existence* m_existence;

    private:
        static void startTimer();
        static std::atomic<unsigned long long> universeTick;
        static bool clockStarted;

    private:
};
#endif // UNIVERSE_H

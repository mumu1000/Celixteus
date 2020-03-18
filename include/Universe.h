#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "SuperCluster.h"

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
        void genSuperCluster(unsigned int generatingPlayerId);
        void update();
        SuperCluster& operator[](unsigned int i);
        unsigned int size(){return m_superClusterList.size();};
        unsigned long long getUniverseTick() const {return m_universeTick;};
        void setUniverseTick(unsigned long long newTickVal){m_universeTick = newTickVal;};
        void increaseUniverseTick(unsigned long long increment){m_universeTick += increment;};
        Existence* getExistence(){return m_existence;};

    protected:
        std::vector<SuperCluster*> m_superClusterList;
        Existence* m_existence;
        unsigned long long m_universeTick;

    private:
};
#endif // UNIVERSE_H

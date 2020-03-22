#ifndef PLAYERPRESENCE_H
#define PLAYERPRESENCE_H

class Player;
class PlayerPresence
{
    public:
        PlayerPresence();
        virtual ~PlayerPresence();
        void addCredits(unsigned long long toBeAdded);
        void setCredits(unsigned long long toBeSet);
        bool subCredits(unsigned long long toBeSubbed);
        void addMinerals(unsigned long long toBeAdded);
        void setMinerals(unsigned long long toBeSet);
        bool subMinerals(unsigned long long toBeSubbed);
        void addMineralCap(unsigned long long toBeAdded);
        void setMineralCap(unsigned long long toBeSet);
        bool subMineralCap(unsigned long long toBeSubbed);
        void addEnergy(unsigned long long toBeAdded);
        void setEnergy(unsigned long long toBeSet);
        bool subEnergy(unsigned long long toBeSubbed);
        unsigned long long getCredits(){return m_credits;};
        unsigned long long getMinerals(){return m_minerals;};
        unsigned long long getMineralCap(){return m_mineralCap;};
        unsigned long long getEnergy(){return m_energy;};
    protected:
        int m_pickaxe;
        unsigned long long m_credits;
        unsigned long long m_minerals;
        unsigned long long m_mineralCap;
        unsigned long long m_energy;
    private:
};

#endif // PLAYERPRESENCE_H

#ifndef PLAYERPRESENCE_H
#define PLAYERPRESENCE_H


class PlayerPresence
{
    public:
        PlayerPresence();
        virtual ~PlayerPresence();
        void addMinerals(unsigned long long toBeAdded);
        void setMinerals(unsigned long long toBeSet);
        bool subMinerals(unsigned long long toBeSubbed);
        void addMineralCap(unsigned long long toBeAdded);
        void setMineralCap(unsigned long long toBeSet);
        bool subMineralCap(unsigned long long toBeSubbed);
        void addEnergy(unsigned long long toBeAdded);
        void setEnergy(unsigned long long toBeSet);
        bool subEnergy(unsigned long long toBeSubbed);
    protected:
        int m_pickaxe;
        unsigned long long m_minerals;
        unsigned long long m_mineralCap;
        unsigned long long m_energy;
    private:
};

#endif // PLAYERPRESENCE_H

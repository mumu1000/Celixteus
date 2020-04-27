#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
class PlayerPresence;
class Player
{
    public:
        Player();
        virtual ~Player();
        void registerPlayerPresence(PlayerPresence* playerPresence);
        unsigned int getPPresCount() {return m_playerPresenceList.size();};

    protected:
        std::vector<PlayerPresence*> m_playerPresenceList;
    private:
};

#endif // PLAYER_H

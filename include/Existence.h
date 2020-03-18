#ifndef EXISTENCE_H
#define EXISTENCE_H
#include <vector>

class Universe;
class Player;
class ExistenceView;
class Existence
{
    public:
        friend ExistenceView;
        Existence();
        virtual ~Existence();
        void genUniverse(unsigned int generatingPlayerId);
        unsigned int newPlayer();
        Player* getPlayerAtId(unsigned int id);
        void update();
        Universe& operator[](unsigned int i);
        unsigned int size(){return m_universeList.size();};
    protected:
        std::vector<Universe*> m_universeList;
        std::vector<Player*> m_playerList;
    private:
};
#endif // EXISTENCE_H

#ifndef EXISTENCE_H
#define EXISTENCE_H
#include <vector>
#include "Universe.h"


class ExistenceView;
class Existence
{
    public:
        friend ExistenceView;
        Existence();
        virtual ~Existence();
        void genUniverse(Player* generatingPlayer);
        void update();
        Universe& operator[](unsigned int i);
        unsigned int size(){return m_universeList.size();};
    protected:
        std::vector<Universe*> m_universeList;

    private:
};
#endif // EXISTENCE_H

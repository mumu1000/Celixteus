#include "Existence.h"
#include "Universe.h"
#include "Player.h"
//THERE IS STILL SOME SHITTY CONSTANT HERE COMON

Existence::Existence()
{
    std::cout << "Création d'une Existence terminée\n";
}

Existence::~Existence()
{

}

void Existence::genUniverse(unsigned int generatingPlayerId)
{
    std::cout << "Universe numero " << (m_universeList.size()+1) << " en cours de création\n";
    m_universeList.push_back(new Universe(this , 5));
    std::cout << "Universe numero " << (m_universeList.size()) << " créé\n";
}


/*unsigned int Existence::registerPlayer(Player* toRegister)
{
    for (unsigned int i = 0; i<m_playerList.size();i++)
    {
        if (m_playerList[i]==toRegister) {return i;}
    }
    m_playerList.push_back(toRegister);
    return (m_playerList.size() - 1);
}*/

unsigned int Existence::newPlayer()
{
    m_playerList.push_back(new Player());
    return (m_playerList.size() - 1);
}


Player* Existence::getPlayerAtId(unsigned int id)
{
    if (id>=m_playerList.size()) {return nullptr;}
    return m_playerList[id];
}


void Existence::update()
{
    for (unsigned int i = 0; i != m_universeList.size() ;i++ )
    {
        m_universeList[i]->update();
    }
}

Universe& Existence::operator[](unsigned int i)
{
    return *m_universeList[i];
}

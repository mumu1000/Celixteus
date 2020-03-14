#include "Existence.h"
//THERE IS STILL SOME SHITTY CONSTANT HERE COMON

Existence::Existence()
{
    std::cout << "Création d'une Existence terminée\n";
}

Existence::~Existence()
{

}

void Existence::genUniverse(Player* generatingPlayer)
{
    std::cout << "Universe numero " << (m_universeList.size()+1) << " en cours de création\n";
    m_universeList.push_back(new Universe(this , 5));
    std::cout << "Universe numero " << (m_universeList.size()) << " créé\n";
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

#include "Universe.h"

//THERE IS STILL SOME SHITTY CONSTANT HERE COMON

Universe::Universe(Existence* existence)
{
    m_existence = existence;
    m_universeTick = 0;
}

Universe::Universe(Existence* existence, unsigned int universeSize)
{
    m_existence = existence;
    m_universeTick = 0;
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


void Universe::update()
{
    for (unsigned int i = 0; i != m_superClusterList.size() ;i++ )
    {
        m_superClusterList[i]->update();
    }
}

SuperCluster& Universe::operator[](unsigned int i)
{
    return *m_superClusterList[i];
}

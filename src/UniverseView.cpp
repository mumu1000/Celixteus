#include "UniverseView.h"

UniverseView::UniverseView(Universe* targetUniverse)
{
    m_targetUniverse = targetUniverse;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
}

UniverseView::~UniverseView()
{
    //dtor
}

void UniverseView::draw()
{
    std::cout << "Je suis une vue de Universe et je dessine un Universe contenant " << (m_targetUniverse->m_superClusterList.size()) << " SuperCluster \n";

    for (unsigned int i = 0; i != m_targetUniverse->m_superClusterList.size() ;i++ )
    {
        std::cout << "I'm drawing SuperCluster number " << (i+1) << "\n";
    }
}

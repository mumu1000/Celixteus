#include "ClusterView.h"
#include <iostream>
ClusterView::ClusterView(Cluster* targetCluster)
{
    m_targetCluster = targetCluster;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
}

ClusterView::~ClusterView()
{
    //dtor
}

void ClusterView::draw()
{
    std::cout << "Je suis une vue de Cluster et je dessine un Cluster contenant " << (m_targetCluster->m_galaxyList.size()) << " Galaxies\n";

    for (unsigned int i = 0; i != m_targetCluster->m_galaxyList.size() ;i++ )
    {
        std::cout << "I'm drawing Galaxy number " << (i+1) << "\n";
    }
}

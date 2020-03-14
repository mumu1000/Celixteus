#include "SuperClusterView.h"

SuperClusterView::SuperClusterView(SuperCluster* targetSuperCluster)
{
    m_targetSuperCluster = targetSuperCluster;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
}

SuperClusterView::~SuperClusterView()
{
    //dtor
}

void SuperClusterView::draw()
{
    std::cout << "Je suis une vue de SuperCluster et je dessine un SuperCluster contenant " << (m_targetSuperCluster->m_clusterList.size()) << " Clusters \n";

    for (unsigned int i = 0; i != m_targetSuperCluster->m_clusterList.size() ;i++ )
    {
        std::cout << "I'm drawing Cluster number " << (i+1) << "\n";
    }
}

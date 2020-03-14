#include "ExistenceView.h"

ExistenceView::ExistenceView(Existence* targetExistence)
{
    m_targetExistence = targetExistence;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
}

ExistenceView::~ExistenceView()
{
    //dtor
}

void ExistenceView::draw()
{
    std::cout << "Je suis une vue d' Existence et je dessine une Existence contenant " << (m_targetExistence->m_universeList.size()) << " Universe\n";

    for (unsigned int i = 0; i != m_targetExistence->m_universeList.size() ;i++ )
    {
        std::cout << "I'm drawing Universe number " << (i+1) << "\n";
    }
}

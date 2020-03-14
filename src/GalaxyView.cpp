#include "GalaxyView.h"

GalaxyView::GalaxyView(Galaxy* targetGalaxy)
{
    m_targetGalaxy = targetGalaxy;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
}

GalaxyView::~GalaxyView()
{
    //dtor
}

void GalaxyView::draw()
{
    std::cout << "Je suis une vue de Galaxy et je dessine une Galaxy contenant " << (m_targetGalaxy->m_solarSysList.size()) << " SolarSys\n";

    for (unsigned int i = 0; i != m_targetGalaxy->m_solarSysList.size() ;i++ )
    {
        std::cout << "I'm drawing SolarSys number " << (i+1) << "\n";
    }
}

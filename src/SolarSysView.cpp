#include "SolarSysView.h"
#include <iostream>

SolarSysView::SolarSysView(SolarSys* targetSolarSys)
{
    m_targetSolarSys = targetSolarSys;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
}

SolarSysView::~SolarSysView()
{
    //dtor
}

void SolarSysView::draw()
{
    std::cout << "Je suis une vue de SolarSys et je dessine un SolarSys contenant " << (m_targetSolarSys->m_planetList.size()) << " Planètes\n";

    for (unsigned int i = 0; i != m_targetSolarSys->m_planetList.size() ;i++ )
    {
        std::cout << "I'm drawing Planet number " << (i+1) << "\n";
    }
}

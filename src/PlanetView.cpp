#include "PlanetView.h"
#include "Planet.h"
#include "TestGUI.h"
#include "SolarSysView.h"
#include <iostream>

PlanetView::PlanetView(Planet* targetPlanet, unsigned int currPlayerId, bool playerIDSet)
{
    m_targetPlanet = targetPlanet;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
}

PlanetView::~PlanetView()
{
    //dtor
}

AbstractView* PlanetView::draw()
{
    using namespace TestGUI;
    std::string toDraw = "Je suis une planète";
    info(toDraw);
    return new SolarSysView(m_targetPlanet->getSolarSys(),m_currPlayerId,m_playerIDSet);
}



#include "PlanetView.h"
#include "Planet.h"
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

void PlanetView::draw()
{
    std::cout << "Je suis une vue et je dessine une planète\n";
    m_targetPlanet->draw(m_xOrigin,m_yOrigin,m_zoom);
}



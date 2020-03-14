#ifndef PLANETVIEW_H
#define PLANETVIEW_H
#include "AbstractView.h"
#include "Planet.h"
#include <iostream>


class Planet;
class PlanetView : public AbstractView
{
    public:
        PlanetView( Planet* targetPlanet);
        virtual ~PlanetView();
        void draw();
    protected:
        Planet* m_targetPlanet;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
    private:
};

#endif // PLANETVIEW_H

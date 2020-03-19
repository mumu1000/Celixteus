#ifndef PLANETVIEW_H
#define PLANETVIEW_H

#include "AbstractView.h"


class Planet;
class PlanetView : public AbstractView
{
    public:
        PlanetView( Planet* targetPlanet, unsigned int currPlayerId, bool playerIDSet);
        virtual ~PlanetView();
        AbstractView* draw();
    protected:
        Planet* m_targetPlanet;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
        unsigned int m_currPlayerId;
        bool m_playerIDSet;
    private:
};

#endif // PLANETVIEW_H

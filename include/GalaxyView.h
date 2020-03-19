#ifndef GALAXYVIEW_H
#define GALAXYVIEW_H

#include <AbstractView.h>

class Galaxy;
class GalaxyView : public AbstractView
{
    public:
        GalaxyView(Galaxy* targetGalaxy, unsigned int currPlayerId, bool playerIDSet);
        virtual ~GalaxyView();
        void draw();
    protected:
        Galaxy* m_targetGalaxy;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
        unsigned int m_currPlayerId;
        bool m_playerIDSet;
    private:
};


#endif // GALAXYVIEW_H

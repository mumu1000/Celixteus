#ifndef GALAXYVIEW_H
#define GALAXYVIEW_H

#include <AbstractView.h>
#include "Galaxy.h"

class GalaxyView : public AbstractView
{
    public:
        GalaxyView(Galaxy* targetGalaxy);
        virtual ~GalaxyView();
        void draw();
    protected:
        Galaxy* m_targetGalaxy;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
    private:
};


#endif // GALAXYVIEW_H

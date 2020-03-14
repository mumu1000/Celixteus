#ifndef SOLARSYSVIEW_H
#define SOLARSYSVIEW_H

#include <AbstractView.h>
#include "SolarSys.h"

class SolarSysView : public AbstractView
{
    public:
        SolarSysView(SolarSys* targetSolarSys);
        virtual ~SolarSysView();
        void draw();
    protected:
        SolarSys* m_targetSolarSys;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
    private:
};

#endif // SOLARSYSVIEW_H

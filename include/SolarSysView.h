#ifndef SOLARSYSVIEW_H
#define SOLARSYSVIEW_H

#include <AbstractView.h>

class SolarSys;
class SolarSysView : public AbstractView
{
    public:
        SolarSysView(SolarSys* targetSolarSys, unsigned int currPlayerId, bool playerIDSet);
        virtual ~SolarSysView();
        void draw();
    protected:
        SolarSys* m_targetSolarSys;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
        unsigned int m_currPlayerId;
        bool m_playerIDSet;
    private:
};

#endif // SOLARSYSVIEW_H

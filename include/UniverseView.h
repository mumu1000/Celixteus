#ifndef UNIVERSEVIEW_H
#define UNIVERSEVIEW_H

#include <AbstractView.h>
#include "Universe.h"
#include "TestGUI.h"

class UniverseView : public AbstractView
{
    public:
        UniverseView(Universe* targetUniverse);
        virtual ~UniverseView();
        void draw();
    protected:
        Universe* m_targetUniverse;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
    private:
};


#endif // UNIVERSEVIEW_H

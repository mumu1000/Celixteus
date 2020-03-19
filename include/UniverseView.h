#ifndef UNIVERSEVIEW_H
#define UNIVERSEVIEW_H

#include <AbstractView.h>

class Universe;
class UniverseView : public AbstractView
{
    public:
        UniverseView(Universe* targetUniverse, unsigned int currPlayerId, bool playerIDSet);
        virtual ~UniverseView();
        AbstractView* draw();
    protected:
        Universe* m_targetUniverse;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
        unsigned int m_currPlayerId;
        bool m_playerIDSet;
    private:
};


#endif // UNIVERSEVIEW_H

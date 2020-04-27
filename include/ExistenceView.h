#ifndef EXISTENCEVIEW_H
#define EXISTENCEVIEW_H
#include <AbstractView.h>

class Existence;
class ExistenceView : public AbstractView
{
    public:
        ExistenceView(Existence* targetExistence);
        ExistenceView(Existence* targetExistence, unsigned int currPlayerId, bool playerIDSet);
        virtual ~ExistenceView();
        AbstractView* draw();
    protected:
        Existence* m_targetExistence;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
        unsigned int m_currPlayerId;
        bool m_playerIDSet;
        void setCurrPlayerID(unsigned int id){m_currPlayerId = id;m_playerIDSet = true;};
        inline void resetCurrPlayerID(){m_playerIDSet = false;};
    private:
};

#endif // EXISTENCEVIEW_H

#ifndef EXISTENCEVIEW_H
#define EXISTENCEVIEW_H
#include <AbstractView.h>
#include "Existence.h"

class ExistenceView : public AbstractView
{
    public:
        ExistenceView(Existence* targetExistence);
        virtual ~ExistenceView();
        void draw();
    protected:
        Existence* m_targetExistence;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
    private:
};

#endif // EXISTENCEVIEW_H

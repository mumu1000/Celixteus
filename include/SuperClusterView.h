#ifndef SUPERCLUSTERVIEW_H
#define SUPERCLUSTERVIEW_H

#include <AbstractView.h>
#include "SuperCluster.h"

class SuperClusterView : public AbstractView
{
    public:
        SuperClusterView(SuperCluster* targetSuperCluster);
        virtual ~SuperClusterView();
        void draw();
    protected:
        SuperCluster* m_targetSuperCluster;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
    private:
};

#endif // SUPERCLUSTERVIEW_H

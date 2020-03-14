#ifndef CLUSTERVIEW_H
#define CLUSTERVIEW_H


#include <AbstractView.h>
#include "Cluster.h"

class ClusterView : public AbstractView
{
    public:
        ClusterView(Cluster* targetCluster);
        virtual ~ClusterView();
        void draw();
    protected:
        Cluster* m_targetCluster;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
    private:
};

#endif // CLUSTERVIEW_H

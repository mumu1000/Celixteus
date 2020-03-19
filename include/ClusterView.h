#ifndef CLUSTERVIEW_H
#define CLUSTERVIEW_H

#include <AbstractView.h>

class Cluster;
class ClusterView : public AbstractView
{
    public:
        ClusterView(Cluster* targetCluster, unsigned int currPlayerId, bool playerIDSet);
        virtual ~ClusterView();
        void draw();
    protected:
        Cluster* m_targetCluster;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
        unsigned int m_currPlayerId;
        bool m_playerIDSet;
    private:
};

#endif // CLUSTERVIEW_H

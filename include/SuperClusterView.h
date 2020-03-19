#ifndef SUPERCLUSTERVIEW_H
#define SUPERCLUSTERVIEW_H

#include <AbstractView.h>

class SuperCluster;
class SuperClusterView : public AbstractView
{
    public:
        SuperClusterView(SuperCluster* targetSuperCluster, unsigned int currPlayerId, bool playerIDSet);
        virtual ~SuperClusterView();
        void draw();
    protected:
        SuperCluster* m_targetSuperCluster;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
        unsigned int m_currPlayerId;
        bool m_playerIDSet;
    private:
};

#endif // SUPERCLUSTERVIEW_H

#ifndef ABSTRACTTILEPLACEABLE_H
#define ABSTRACTTILEPLACEABLE_H
#include "Tile.h"
#include "Planet.h"
#include "SolarSys.h"
#include "Galaxy.h"
#include "Cluster.h"
#include "SuperCluster.h"
#include "Universe.h"

class Tile;
class AbstractTilePlaceable
{
    public:
        AbstractTilePlaceable(Tile* slot);
        virtual ~AbstractTilePlaceable();
        virtual void draw(float xOrigin, float yOrigin, float zoom, unsigned int xPos, unsigned int yPos)=0;
        virtual void update()=0;
    protected:
        Tile* m_slot;
        unsigned long long m_lastTickUpdated;
    private:
};

#endif // ABSTRACTTILEPLACEABLE_H

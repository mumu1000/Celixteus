#ifndef TILEMINER_H
#define TILEMINER_H

#include "AbstractTilePlaceable.h"

class Tile;
class TileMiner : public AbstractTilePlaceable
{
    public:
        TileMiner(Tile* slot);
        virtual ~TileMiner();
        virtual void update();

    protected:

    private:
};

#endif // TILEMINER_H

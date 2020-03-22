#include "TileMiner.h"
#include "Tile.h"
#include "Planet.h"
#include "Universe.h"
#include <tuple>

TileMiner::TileMiner(Tile* slot) : AbstractTilePlaceable(slot)
{
    m_levels = std::make_tuple(1,1,0);
    m_type = AbstractTilePlaceable::Miner;
}

TileMiner::~TileMiner()
{
    //dtor
}


void TileMiner::update()
{

}


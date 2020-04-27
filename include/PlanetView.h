#ifndef PLANETVIEW_H
#define PLANETVIEW_H

#include "AbstractView.h"
#include <vector>
#include <string>

class Tile;
class Planet;
class PlanetView : public AbstractView
{
    public:
        PlanetView( Planet* targetPlanet, unsigned int currPlayerId, bool playerIDSet);
        virtual ~PlanetView();
        AbstractView* draw();
    protected:
        Planet* m_targetPlanet;
        float m_xOrigin;
        float m_yOrigin;
        float m_zoom;
        unsigned int m_currPlayerId;
        bool m_playerIDSet;
        std::vector<Tile*> m_selection;
        std::string DescTile(Tile* tileToDesc);
        bool isSelected(Tile* toTest);
        bool isSelected(unsigned int idToTest);
        void displaySelected();

        Tile* askTile(bool any, bool mustBeFree);
        std::tuple<int,int,int> askUpgrade();
    private:
};

#endif // PLANETVIEW_H

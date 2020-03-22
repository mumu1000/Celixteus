#include "PlanetView.h"
#include "Planet.h"
#include "TestGUI.h"
#include "SolarSysView.h"
#include "Universe.h"
#include <iostream>
#include "Tile.h"
#include "AbstractTilePlaceable.h"
#include "TileMiner.h"

PlanetView::PlanetView(Planet* targetPlanet, unsigned int currPlayerId, bool playerIDSet)
{
    m_targetPlanet = targetPlanet;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
    m_currPlayerId = currPlayerId;
    m_playerIDSet = playerIDSet;
}

PlanetView::~PlanetView()
{
    //dtor
}

AbstractView* PlanetView::draw()
{
    using namespace TestGUI;
    if (m_targetPlanet == nullptr)
    {
        std::string towrite = "Broken PlanetView: Pointed Planet is nullptr\nReturning.";
        info(towrite);
        return nullptr;
    }
    if (!m_playerIDSet || m_targetPlanet->getOwner() != m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId))
    {
        std::string towrite = "Cannot Access Planet As This Player\nGoing back one hierarchical level.";
        info(towrite);
        return new SolarSysView(m_targetPlanet->getSolarSys(),m_currPlayerId,m_playerIDSet);
    }


    bool quit = false;
    do
    {
        std::vector<std::pair<std::string,unsigned int>> options;

        options.push_back(std::make_pair("Selection Tools",0));
        options.push_back(std::make_pair("Build",1));
        options.push_back(std::make_pair("List Tiles",2));
        options.push_back(std::make_pair("Return",3));
        unsigned int response = menu(options);

        switch(response)
        {

        case 0:
            {
                bool quitSelection = false;
                do
                {
                    std::vector<std::pair<std::string,unsigned int>> optionsSelection;
                    for (unsigned int i = 0; i<m_targetPlanet->size();i++)
                    {
                        if (!isSelected(i))
                        {
                            std::string temp1 = "Tile " + std::to_string(i) + " : " + DescTile(&((*m_targetPlanet)[i]));
                            optionsSelection.push_back(std::make_pair(temp1,i));
                        }
                    }
                    optionsSelection.push_back(std::make_pair("Clear Selection",m_targetPlanet->size()));
                    optionsSelection.push_back(std::make_pair("Display Selection",m_targetPlanet->size()+1));
                    optionsSelection.push_back(std::make_pair("Return",m_targetPlanet->size()+2));
                    unsigned int selectedTile = menu(optionsSelection);
                    if (selectedTile==m_targetPlanet->size()) {m_selection.clear();continue;}
                    if (selectedTile==m_targetPlanet->size()+1) {displaySelected();continue;}
                    if (selectedTile==m_targetPlanet->size()+2) {quitSelection = true;continue;}
                    if ( !isSelected(selectedTile)){m_selection.push_back(&((*m_targetPlanet)[selectedTile]));}
                } while (!quitSelection);
                break;
            }

        case 1:
        //1 : Choisis quoi construire
        //2 : Appelle build sur toute la selection

            {
                std::vector<std::pair<std::string,AbstractTilePlaceable::BuildingType>> optionsConstruction;
                optionsConstruction.push_back(std::make_pair("Crystal Miner",AbstractTilePlaceable::Miner));
                optionsConstruction.push_back(std::make_pair("Return",AbstractTilePlaceable::Nothing));
                auto buildingSelected = menu(optionsConstruction);
                if (buildingSelected == AbstractTilePlaceable::Nothing){break;}
                for (unsigned int i = 0; i<m_selection.size();i++)
                {
                    m_selection[i]->build(buildingSelected);
                }
                break;
            }

        case 2:
        {
            std::string toDisplay;
            for (unsigned int i = 0; i<m_targetPlanet->size();i++)
            {
                toDisplay = toDisplay + "Tile " + std::to_string(i) + " : " + DescTile(&((*m_targetPlanet)[i])) +"\n";
            }
            TestGUI::info(toDisplay);
            break;
        }
        case 3:
            quit=true;
            break;
        }

    }while (!quit);
    return new SolarSysView(m_targetPlanet->getSolarSys(),m_currPlayerId,m_playerIDSet);
}



std::string PlanetView::DescTile(Tile* tileToDesc)
{

    std::string toReturn;
    if (tileToDesc->getTileContent() == nullptr)
    {
        toReturn = "Empty Tile";
        return toReturn;
    }
    if (tileToDesc->getTileContent()->getType() == AbstractTilePlaceable::Miner)
    {
        toReturn = "Mining Tile level " + std::to_string(std::get<0>(tileToDesc->getTileContent()->getLevels())) + ":" + std::to_string(std::get<1>(tileToDesc->getTileContent()->getLevels())) + ":" + std::to_string(std::get<2>(tileToDesc->getTileContent()->getLevels()));
        return toReturn;
    }
    toReturn = "Weird Tile (Please Report)";

    return toReturn;
}

bool PlanetView::isSelected(Tile* toTest)
{
    for (unsigned int i = 0; i<m_selection.size();i++)
    {
        if (m_selection[i]==toTest) {return true;}
    }
    return false;
}

bool PlanetView::isSelected(unsigned int idToTest)
{
    return isSelected(&((*m_targetPlanet)[idToTest]));
}



void PlanetView::displaySelected()
{
    std::string toDisplay;
    for (unsigned int i = 0; i<m_targetPlanet->size();i++)
    {
        if (isSelected(i))
        {
            toDisplay = toDisplay + "Tile " + std::to_string(i) + " : " + DescTile(&((*m_targetPlanet)[i])) +"\n";
        }
    }
    TestGUI::info(toDisplay);
}



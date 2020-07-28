#include "PlanetView.h"
#include "Planet.h"
#include "TestGUI.h"
#include "PlayerGUI.h"
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
    using namespace PlayerGUI;
    if (m_targetPlanet == nullptr)
    {
        std::string towrite = "Broken PlanetView: Pointed Planet is nullptr\nReturning.";
        TestGUI::info(towrite);
        return nullptr;
    }
    if (!m_playerIDSet || m_targetPlanet->getOwner() != m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId))
    {
        std::string towrite = "Cannot Access Planet As This Player\nGoing back one hierarchical level.";
        TestGUI::info(towrite);
        return new SolarSysView(m_targetPlanet->getSolarSys(),m_currPlayerId,m_playerIDSet);
    }


    bool quit = false;
    do
    {
        std::vector<std::pair<std::string,unsigned int>> options;

        options.push_back(std::make_pair("Selection Tools",0));
        options.push_back(std::make_pair("Update",6));
        options.push_back(std::make_pair("Collect",5));
        options.push_back(std::make_pair("Build",1));
        options.push_back(std::make_pair("Upgrade",2));
        options.push_back(std::make_pair("List Tiles",3));
        options.push_back(std::make_pair("Return",4));
        unsigned int response = menu(options,m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId));

        switch(response)
        {

        case 0:
            {
                bool quitSelection = false;
                unsigned int lastOpt = 0;
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
                    unsigned int selectedPlanet = menu(optionsSelection,lastOpt,m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId));
                    if (selectedPlanet==m_targetPlanet->size()) {m_selection.clear();continue;}
                    if (selectedPlanet==m_targetPlanet->size()+1) {displaySelected();continue;}
                    if (selectedPlanet==m_targetPlanet->size()+2) {quitSelection = true;continue;}
                    if ( !isSelected(selectedPlanet)){m_selection.push_back(&((*m_targetPlanet)[selectedPlanet]));}
                    selectedPlanet--;
                } while (!quitSelection);
                break;
            }

        case 1:
            {
                bool selectionWasClear=false;
                if (m_selection.size()==0)
                {
                    selectionWasClear =true;
                    Tile* temp = askTile(false,true);
                    if (temp == nullptr){break;}
                    m_selection.push_back(temp);
                }
                std::vector<std::pair<std::string,AbstractTilePlaceable::BuildingType>> optionsConstruction;
                optionsConstruction.push_back(std::make_pair("Crystal Miner",AbstractTilePlaceable::Miner));
                optionsConstruction.push_back(std::make_pair("Ore Storage Building",AbstractTilePlaceable::OreStorage));
                optionsConstruction.push_back(std::make_pair("Energy Collector",AbstractTilePlaceable::EnergyColl));
                optionsConstruction.push_back(std::make_pair("Return",AbstractTilePlaceable::Nothing));
                auto buildingSelected = menu(optionsConstruction,m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId));
                if (buildingSelected == AbstractTilePlaceable::Nothing){break;}
                for (unsigned int i = 0; i<m_selection.size();i++)
                {
                    m_selection[i]->build(buildingSelected);
                }
                if (selectionWasClear){m_selection.clear();}
                break;
            }
        case 2:
            {
                bool selectionWasClear=false;
                if (m_selection.size()==0)
                {
                    selectionWasClear =true;
                    Tile* temp = askTile(false,false);
                    if (temp == nullptr){break;}
                    m_selection.push_back(temp);
                }
                std::tuple<int,int,int> upgradeValues = askUpgrade();
                for (unsigned int i = 0; i<m_selection.size();i++)
                {
                    m_selection[i]->upgrade(upgradeValues);
                }
                if (selectionWasClear){m_selection.clear();}
                break;
            }






        case 3:
            {
                std::string toDisplay;
                for (unsigned int i = 0; i<m_targetPlanet->size();i++)
                {
                    toDisplay = toDisplay + "Tile " + std::to_string(i) + " : " + DescTile(&((*m_targetPlanet)[i])) +"\n";
                }
                TestGUI::info(toDisplay);
                break;
            }
        case 4:
            quit=true;
            break;
        case 5:
            for (unsigned int i = 0; i<m_selection.size();i++)
            {
                if (m_selection[i]->getTileContent() != nullptr)
                m_selection[i]->getTileContent()->collect(m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId));
            }
            break;
        case 6:
            for (unsigned int i = 0; i<m_selection.size();i++)
            {
                if (m_selection[i]->getTileContent() != nullptr)
                m_selection[i]->getTileContent()->update(m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId));
            }
            break;
        }

    }while (!quit);
    return new SolarSysView(m_targetPlanet->getSolarSys(),m_currPlayerId,m_playerIDSet);
}



std::string PlanetView::DescTile(Tile* tileToDesc)
{
    if (tileToDesc->getTileContent() == nullptr)
    {
        std::string toReturn("Empty Tile");
        return toReturn;
    }

    return tileToDesc->getTileContent()->description();
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

Tile* PlanetView::askTile(bool any, bool mustBeFree)
{
    std::vector<std::pair<std::string,unsigned int>> tileSelection;
    for (unsigned int i = 0; i<m_targetPlanet->size();i++)
    {
        if (any || (mustBeFree && ((*m_targetPlanet)[i]).getTileContent() == nullptr) || (!mustBeFree && ((*m_targetPlanet)[i]).getTileContent() != nullptr) )
        {
            std::string temp1 = "Tile " + std::to_string(i) + " : " + DescTile(&((*m_targetPlanet)[i]));
            tileSelection.push_back(std::make_pair(temp1,i));
        }
    }
    tileSelection.push_back(std::make_pair("Return",m_targetPlanet->size()));
    unsigned int selectedTile = PlayerGUI::menu(tileSelection,m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId));
    if (selectedTile==m_targetPlanet->size()) {return nullptr;}
    return &((*m_targetPlanet)[selectedTile]);
}

std::tuple<int,int,int> PlanetView::askUpgrade()
{
    std::vector<std::pair<std::string,int>> upgradeValues;

    upgradeValues.push_back(std::make_pair("Upgrade Path 1",0));
    upgradeValues.push_back(std::make_pair("Upgrade Path 2",0));
    upgradeValues.push_back(std::make_pair("Upgrade Path 3",0));
    PlayerGUI::sliders(upgradeValues,false,m_targetPlanet->getUniverse()->getPlayerPresOfId(m_currPlayerId));
    return std::make_tuple(upgradeValues[0].second,upgradeValues[1].second,upgradeValues[2].second);
}











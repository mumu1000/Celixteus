#include "SolarSysView.h"
#include "PlanetView.h"
#include "TestGUI.h"
#include "PlayerGUI.h"
#include "Universe.h"
#include "SolarSys.h"
#include "GalaxyView.h"
#include "Planet.h"
#include <iostream>

SolarSysView::SolarSysView(SolarSys* targetSolarSys, unsigned int currPlayerId, bool playerIDSet)
{
    m_targetSolarSys = targetSolarSys;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
    m_currPlayerId = currPlayerId;
    m_playerIDSet = playerIDSet;
}

SolarSysView::~SolarSysView()
{
    //dtor
}

AbstractView* SolarSysView::draw()
{
    using namespace PlayerGUI;
    if (m_targetSolarSys == nullptr)
    {
        std::string towrite = "Broken SolarSysView: Pointed SolarSys is nullptr\nReturning.";
        TestGUI::info(towrite);
        return this;
    }


    bool quit = false;
    do
    {
        std::vector<std::pair<std::string,unsigned int>> options;

        if (m_playerIDSet)
        {
            options.push_back(std::make_pair("Goto Planet",0));
            options.push_back(std::make_pair("Generate Planet",1));
        }
        options.push_back(std::make_pair("List Planets",2));
        options.push_back(std::make_pair("Return",3));
        unsigned int response = menu(options,m_targetSolarSys->getUniverse()->getPlayerPresOfId(m_currPlayerId));
        switch(response)
        {
        case 0:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsPlanet;
                for (unsigned int i = 0; i<m_targetSolarSys->m_planetList.size();i++)
                {
                    if (&(*m_targetSolarSys)[i] != nullptr && ((*m_targetSolarSys)[i]).getOwner() == m_targetSolarSys->getUniverse()->getPlayerPresOfId(m_currPlayerId))
                    {
                        const std::string temp1 = "Planet ";
                        std::string temp2 = std::to_string(i);
                        optionsPlanet.push_back(std::make_pair(temp1+temp2,i));
                    }
                }
                optionsPlanet.push_back(std::make_pair("Return",m_targetSolarSys->m_planetList.size()));
                unsigned int selectedPlanet = menu(optionsPlanet,m_targetSolarSys->getUniverse()->getPlayerPresOfId(m_currPlayerId));
                if (selectedPlanet==m_targetSolarSys->m_planetList.size()) {break;}
                PlanetView* planetView = new PlanetView(&(*m_targetSolarSys)[selectedPlanet],m_currPlayerId,m_playerIDSet);
                return planetView;
                break;
            }
        case 1:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsPlanet;
                for (unsigned int i = 0; i<m_targetSolarSys->m_planetList.size();i++)
                {
                    if (m_targetSolarSys->m_planetList[i] == nullptr)
                    {
                        const std::string temp1 = "Unknown Planet ";
                        std::string temp2 = std::to_string(i);
                        optionsPlanet.push_back(std::make_pair(temp1+temp2,i));
                    }

                }
                optionsPlanet.push_back(std::make_pair("Return",m_targetSolarSys->m_planetList.size()));
                unsigned int selectedPlanet = menu(optionsPlanet,m_targetSolarSys->getUniverse()->getPlayerPresOfId(m_currPlayerId));
                if (selectedPlanet==m_targetSolarSys->m_planetList.size()) {break;}
                m_targetSolarSys->genPlanet(m_currPlayerId,selectedPlanet);
                break;
            }
        case 2:
            {
                std::string toWrite;
                for (unsigned int i = 0; i<m_targetSolarSys->m_planetList.size();i++)
                {
                    if (m_targetSolarSys->m_planetList[i] != nullptr)
                    toWrite = toWrite + "Planet " + std::to_string(i) + "\n";
                }
                TestGUI::info(toWrite);
                break;
            }
        case 3:
            quit=true;
            break;
        }
    }while (!quit);
    return new GalaxyView(m_targetSolarSys->getGalaxy(),m_currPlayerId,m_playerIDSet);

}

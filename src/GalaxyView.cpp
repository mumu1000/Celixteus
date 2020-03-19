#include "GalaxyView.h"
#include "SolarSysView.h"
#include "TestGUI.h"
#include "Galaxy.h"
#include "ClusterView.h"
#include <iostream>

GalaxyView::GalaxyView(Galaxy* targetGalaxy, unsigned int currPlayerId, bool playerIDSet)
{
    m_targetGalaxy = targetGalaxy;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
    m_currPlayerId = currPlayerId;
    m_playerIDSet = playerIDSet;
}

GalaxyView::~GalaxyView()
{
    //dtor
}

AbstractView* GalaxyView::draw()
{
    using namespace TestGUI;
    if (m_targetGalaxy == nullptr)
    {
        std::string towrite = "Broken GalaxyView: Pointed Galaxy is nullptr\nReturning.";
        info(towrite);
        return this;
    }


    bool quit = false;
    do
    {
        std::vector<std::pair<std::string,unsigned int>> options;

        options.push_back(std::make_pair("Goto SolarSys",0));
        if (m_playerIDSet)
        {
            options.push_back(std::make_pair("Generate SolarSys",1));
        }
        options.push_back(std::make_pair("List SolarSyss",2));
        options.push_back(std::make_pair("Return",3));
        unsigned int response = menu(options);
        switch(response)
        {
        case 0:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsSolarSys;
                for (unsigned int i = 0; i<m_targetGalaxy->m_solarSysList.size();i++)
                {
                    if (m_targetGalaxy->m_solarSysList[i] != nullptr)
                    {
                        const std::string temp1 = "SolarSys ";
                        std::string temp2 = std::to_string(i);
                        optionsSolarSys.push_back(std::make_pair(temp1+temp2,i));
                    }
                }
                optionsSolarSys.push_back(std::make_pair("Return",m_targetGalaxy->m_solarSysList.size()));
                unsigned int selectedSolarSys = menu(optionsSolarSys);
                if (selectedSolarSys==m_targetGalaxy->m_solarSysList.size()) {break;}
                SolarSysView* solarSysView = new SolarSysView(&(*m_targetGalaxy)[selectedSolarSys],m_currPlayerId,m_playerIDSet);
                return solarSysView;
                break;
            }
        case 1:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsSolarSys;
                for (unsigned int i = 0; i<m_targetGalaxy->m_solarSysList.size();i++)
                {
                    if (m_targetGalaxy->m_solarSysList[i] == nullptr)
                    {
                        const std::string temp1 = "Unknown SolarSys ";
                        std::string temp2 = std::to_string(i);
                        optionsSolarSys.push_back(std::make_pair(temp1+temp2,i));
                    }

                }
                optionsSolarSys.push_back(std::make_pair("Return",m_targetGalaxy->m_solarSysList.size()));
                unsigned int selectedSolarSys = menu(optionsSolarSys);
                if (selectedSolarSys==m_targetGalaxy->m_solarSysList.size()) {break;}
                m_targetGalaxy->genSolarSys(m_currPlayerId,selectedSolarSys);
                break;
            }
        case 2:
            {
                std::string toWrite;
                for (unsigned int i = 0; i<m_targetGalaxy->m_solarSysList.size();i++)
                {
                    if (m_targetGalaxy->m_solarSysList[i] != nullptr)
                    toWrite = toWrite + "SolarSys " + std::to_string(i) + "\n";
                }
                info(toWrite);
                break;
            }
        case 3:
            quit=true;
            break;
        }
    }while (!quit);
    return new ClusterView(m_targetGalaxy->getCluster(),m_currPlayerId,m_playerIDSet);

}

#include "ClusterView.h"
#include "GalaxyView.h"
#include "TestGUI.h"
#include "PlayerGUI.h"
#include "Universe.h"
#include "Cluster.h"
#include "SuperClusterView.h"
#include <iostream>

ClusterView::ClusterView(Cluster* targetCluster, unsigned int currPlayerId, bool playerIDSet)
{
    m_targetCluster = targetCluster;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
    m_currPlayerId = currPlayerId;
    m_playerIDSet = playerIDSet;
}

ClusterView::~ClusterView()
{
    //dtor
}

AbstractView* ClusterView::draw()
{
    using namespace PlayerGUI;
    if (m_targetCluster == nullptr)
    {
        std::string towrite = "Broken ClusterView: Pointed Cluster is nullptr\nReturning.";
        TestGUI::info(towrite);
        return this;
    }

    bool quit = false;
    do
    {
        std::vector<std::pair<std::string,unsigned int>> options;

        options.push_back(std::make_pair("Goto Galaxy",0));
        if (m_playerIDSet)
        {
            options.push_back(std::make_pair("Generate Galaxy",1));
        }
        options.push_back(std::make_pair("List Galaxies",2));
        options.push_back(std::make_pair("Return",3));
        unsigned int response = menu(options,m_targetCluster->getUniverse()->getPlayerPresOfId(m_currPlayerId));
        switch(response)
        {
        case 0:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsGalaxy;
                for (unsigned int i = 0; i<m_targetCluster->m_galaxyList.size();i++)
                {
                    if (m_targetCluster->m_galaxyList[i] != nullptr)
                    {
                        const std::string temp1 = "Galaxy ";
                        std::string temp2 = std::to_string(i);
                        optionsGalaxy.push_back(std::make_pair(temp1+temp2,i));
                    }
                }
                optionsGalaxy.push_back(std::make_pair("Return",m_targetCluster->m_galaxyList.size()));
                unsigned int selectedGalaxy = menu(optionsGalaxy,m_targetCluster->getUniverse()->getPlayerPresOfId(m_currPlayerId));
                if (selectedGalaxy==m_targetCluster->m_galaxyList.size()) {break;}
                GalaxyView* galaxyView = new GalaxyView(&(*m_targetCluster)[selectedGalaxy],m_currPlayerId,m_playerIDSet);
                return galaxyView;
                break;
            }
        case 1:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsGalaxy;
                for (unsigned int i = 0; i<m_targetCluster->m_galaxyList.size();i++)
                {
                    if (m_targetCluster->m_galaxyList[i] == nullptr)
                    {
                        const std::string temp1 = "Unknown Galaxy ";
                        std::string temp2 = std::to_string(i);
                        optionsGalaxy.push_back(std::make_pair(temp1+temp2,i));
                    }

                }
                optionsGalaxy.push_back(std::make_pair("Return",m_targetCluster->m_galaxyList.size()));
                unsigned int selectedGalaxy = menu(optionsGalaxy,m_targetCluster->getUniverse()->getPlayerPresOfId(m_currPlayerId));
                if (selectedGalaxy==m_targetCluster->m_galaxyList.size()) {break;}
                m_targetCluster->genGalaxy(m_currPlayerId,selectedGalaxy);
                break;
            }
        case 2:
            {
                std::string toWrite;
                for (unsigned int i = 0; i<m_targetCluster->m_galaxyList.size();i++)
                {
                    if (m_targetCluster->m_galaxyList[i] != nullptr)
                    toWrite = toWrite + "Galaxy " + std::to_string(i) + "\n";
                }
                TestGUI::info(toWrite);
                break;
            }
        case 3:
            quit=true;
            break;
        }
    }while (!quit);
    return new SuperClusterView(m_targetCluster->getSuperCluster(),m_currPlayerId,m_playerIDSet);

}

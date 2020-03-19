#include "UniverseView.h"
#include "SuperClusterView.h"
#include "TestGUI.h"
#include "Universe.h"
#include "ExistenceView.h"
#include <iostream>

UniverseView::UniverseView(Universe* targetUniverse, unsigned int currPlayerId, bool playerIDSet)
{
    m_targetUniverse = targetUniverse;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
    m_currPlayerId = currPlayerId;
    m_playerIDSet = playerIDSet;
}

UniverseView::~UniverseView()
{
    //dtor
}

AbstractView* UniverseView::draw()
{
    using namespace TestGUI;
    if (m_targetUniverse == nullptr)
    {
        std::string towrite = "Broken UniverseView: Pointed Universe is nullptr\nReturning.";
        info(towrite);
        return this;
    }


    bool quit = false;
    do
    {
        std::vector<std::pair<std::string,unsigned int>> options;

        options.push_back(std::make_pair("Goto SuperCluster",0));
        if (m_playerIDSet)
        {
            options.push_back(std::make_pair("Generate SuperCluster",1));
        }
        options.push_back(std::make_pair("List SuperClusters",2));
        options.push_back(std::make_pair("Return",3));
        unsigned int response = menu(options);
        switch(response)
        {
        case 0:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsSClust;
                for (unsigned int i = 0; i<m_targetUniverse->m_superClusterList.size();i++)
                {
                    if (m_targetUniverse->m_superClusterList[i] != nullptr)
                    {
                        const std::string temp1 = "SuperCluster ";
                        std::string temp2 = std::to_string(i);
                        optionsSClust.push_back(std::make_pair(temp1+temp2,i));
                    }
                }
                optionsSClust.push_back(std::make_pair("Return",m_targetUniverse->m_superClusterList.size()));
                unsigned int selectedSCluster = menu(optionsSClust);
                if (selectedSCluster==m_targetUniverse->m_superClusterList.size()) {break;}
                SuperClusterView* superClusterView = new SuperClusterView(&(*m_targetUniverse)[selectedSCluster],m_currPlayerId,m_playerIDSet);
                return superClusterView;
                break;
            }
        case 1:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsSClust;
                for (unsigned int i = 0; i<m_targetUniverse->m_superClusterList.size();i++)
                {
                    if (m_targetUniverse->m_superClusterList[i] == nullptr)
                    {
                        const std::string temp1 = "Unknown SuperCluster ";
                        std::string temp2 = std::to_string(i);
                        optionsSClust.push_back(std::make_pair(temp1+temp2,i));
                    }

                }
                optionsSClust.push_back(std::make_pair("Return",m_targetUniverse->m_superClusterList.size()));
                unsigned int selectedSCluster = menu(optionsSClust);
                if (selectedSCluster==m_targetUniverse->m_superClusterList.size()) {break;}
                m_targetUniverse->genSuperCluster(m_currPlayerId,selectedSCluster);
                break;
            }
        case 2:
            {
                std::string toWrite;
                for (unsigned int i = 0; i<m_targetUniverse->m_superClusterList.size();i++)
                {
                    if (m_targetUniverse->m_superClusterList[i] != nullptr)
                    toWrite = toWrite + "SuperCluster " + std::to_string(i) + "\n";
                }
                info(toWrite);
                break;
            }
        case 3:
            quit=true;
            break;
        }
    }while (!quit);
    return new ExistenceView(m_targetUniverse->getExistence(),m_currPlayerId,m_playerIDSet);

}


#include "SuperClusterView.h"
#include "ClusterView.h"
#include "TestGUI.h"
#include "SuperCluster.h"
#include <iostream>

SuperClusterView::SuperClusterView(SuperCluster* targetSuperCluster, unsigned int currPlayerId, bool playerIDSet)
{
    m_targetSuperCluster = targetSuperCluster;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
    m_currPlayerId = currPlayerId;
    m_playerIDSet = playerIDSet;
}

SuperClusterView::~SuperClusterView()
{
    //dtor
}

void SuperClusterView::draw()
{
    using namespace TestGUI;
    if (m_targetSuperCluster == nullptr)
    {
        std::string towrite = "Broken SuperClusterView: Pointed SuperCluster is nullptr\nReturning.";
        info(towrite);
        return;
    }


    bool quit = false;
    do
    {
        std::vector<std::pair<std::string,unsigned int>> options;

        options.push_back(std::make_pair("Goto Cluster",0));
        if (m_playerIDSet)
        {
            options.push_back(std::make_pair("Generate Cluster",1));
        }
        options.push_back(std::make_pair("List Clusters",2));
        options.push_back(std::make_pair("Return",3));
        unsigned int response = menu(options);
        switch(response)
        {
        case 0:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsClust;
                for (unsigned int i = 0; i<m_targetSuperCluster->m_clusterList.size();i++)
                {
                    if (m_targetSuperCluster->m_clusterList[i] != nullptr)
                    {
                        const std::string temp1 = "Cluster ";
                        std::string temp2 = std::to_string(i);
                        optionsClust.push_back(std::make_pair(temp1+temp2,i));
                    }
                }
                optionsClust.push_back(std::make_pair("Return",m_targetSuperCluster->m_clusterList.size()));
                unsigned int selectedCluster = menu(optionsClust);
                if (selectedCluster==m_targetSuperCluster->m_clusterList.size()) {break;}
                ClusterView* clusterView = new ClusterView(&(*m_targetSuperCluster)[selectedCluster],m_currPlayerId,m_playerIDSet);
                clusterView->draw();
                delete clusterView;
                break;
            }
        case 1:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsClust;
                for (unsigned int i = 0; i<m_targetSuperCluster->m_clusterList.size();i++)
                {
                    if (m_targetSuperCluster->m_clusterList[i] == nullptr)
                    {
                        const std::string temp1 = "Unknown Cluster ";
                        std::string temp2 = std::to_string(i);
                        optionsClust.push_back(std::make_pair(temp1+temp2,i));
                    }

                }
                optionsClust.push_back(std::make_pair("Return",m_targetSuperCluster->m_clusterList.size()));
                unsigned int selectedCluster = menu(optionsClust);
                if (selectedCluster==m_targetSuperCluster->m_clusterList.size()) {break;}
                m_targetSuperCluster->genCluster(m_currPlayerId,selectedCluster);
                break;
            }
        case 2:
            {
                std::string toWrite;
                for (unsigned int i = 0; i<m_targetSuperCluster->m_clusterList.size();i++)
                {
                    if (m_targetSuperCluster->m_clusterList[i] != nullptr)
                    toWrite = toWrite + "Cluster " + std::to_string(i) + "\n";
                }
                info(toWrite);
                break;
            }
        case 3:
            quit=true;
            break;
        }
    }while (!quit);

}

#include "ExistenceView.h"
#include "TestGUI.h"
#include <string>
#include "UniverseView.h"
ExistenceView::ExistenceView(Existence* targetExistence)
{
    m_targetExistence = targetExistence;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
    m_currPlayerId = 0;
    m_playerIDSet = false;
}

ExistenceView::ExistenceView(Existence* targetExistence, unsigned int currPlayerId, bool playerIDSet)
{
    m_targetExistence = targetExistence;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
    m_currPlayerId = currPlayerId;
    m_playerIDSet = playerIDSet;
}


ExistenceView::~ExistenceView()
{
    //dtor
}

AbstractView* ExistenceView::draw()
{
    using namespace TestGUI;
    if (m_targetExistence == nullptr)
    {
        std::string towrite = "Broken Existence View: Pointed existence is nullptr\nReturning.";
        info(towrite);
        return this;
    }


    bool quit = false;
    do
    {
        std::vector<std::pair<std::string,unsigned int>> options;

        options.push_back(std::make_pair("Create New Player and Select It",0));
        if (m_targetExistence->m_playerList.size()>0)
        {
            options.push_back(std::make_pair("Select a Player",1));
        }
        options.push_back(std::make_pair("Goto Universe",2));
        if (m_playerIDSet)
        {
            options.push_back(std::make_pair("Generate Universe",3));
        }
        options.push_back(std::make_pair("List Universes",4));
        options.push_back(std::make_pair("Quit",5));
        unsigned int response = menu(options);
        switch(response)
        {
        case 0:
            m_currPlayerId = m_targetExistence->newPlayer();
            m_playerIDSet = true;
            break;
        case 1:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsPlayer;
                for (unsigned int i = 0; i<m_targetExistence->m_playerList.size();i++)
                {
                    const std::string temp1 = "Player ";
                    std::string temp2 = std::to_string(i);
                    optionsPlayer.push_back(std::make_pair(temp1+temp2,i));
                }
                optionsPlayer.push_back(std::make_pair("Return",m_targetExistence->m_playerList.size()));
                unsigned int selectedPlayer = menu(optionsPlayer);
                if (selectedPlayer==m_targetExistence->m_playerList.size()) {break;}
                m_currPlayerId = selectedPlayer;
                m_playerIDSet = true;
                break;
            }
        case 2:
            {
                std::vector<std::pair<std::string,unsigned int>> optionsUniverse;
                for (unsigned int i = 0; i<m_targetExistence->m_universeList.size();i++)
                {
                    const std::string temp1 = "Universe ";
                    std::string temp2 = std::to_string(i);
                    optionsUniverse.push_back(std::make_pair(temp1+temp2,i));
                }
                optionsUniverse.push_back(std::make_pair("Return",m_targetExistence->m_universeList.size()));
                unsigned int selectedUniverse = menu(optionsUniverse);
                if (selectedUniverse==m_targetExistence->m_universeList.size()) {break;}
                UniverseView* universeView = new UniverseView(&(*m_targetExistence)[selectedUniverse],m_currPlayerId,m_playerIDSet);
                return universeView;
                break;
            }
        case 3:
            m_targetExistence->genUniverse(m_currPlayerId);
            break;
        case 4:
            {
                std::string toWrite;
                for (unsigned int i = 0; i<m_targetExistence->m_universeList.size();i++)
                {
                    toWrite = toWrite + "Universe " + std::to_string(i) + "\n";
                }
                info(toWrite);
                break;
            }
        case 5:
            quit=true;
            break;
        }
    }while (!quit);
    return nullptr;
}












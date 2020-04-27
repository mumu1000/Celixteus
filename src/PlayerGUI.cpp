#include "PlayerGUI.h"
#include "Player.h"
#include "PlayerPresence.h"

    void PlayerGUI::sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative, Player* targetPlayer)
    {
        std::string desc;
        descPlayer(targetPlayer,desc);
        return TestGUI::sliders(options,canBeNegative,desc);
    }

    void PlayerGUI::sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative, PlayerPresence* targetPlayerPres)
    {
        std::string desc;
        descPlayerPres(targetPlayerPres,desc);
        return TestGUI::sliders(options,canBeNegative,desc);
    }


    void PlayerGUI::descPlayer(Player* targetPlayer, std::string& resultString)
    {
        resultString = "";
        if (targetPlayer != nullptr)
        {
            resultString = "The selected player is present in " + std::to_string(targetPlayer->getPPresCount()) + " Universes";
        }
    }

    void PlayerGUI::descPlayerPres(PlayerPresence* targetPlayerPres, std::string& resultString)
    {
        resultString = "";
        if (targetPlayerPres != nullptr)
        {
            resultString =  "Credits: "+ std::to_string(targetPlayerPres->getCredits()) + " $\n" + \
                            "Minerals: " + std::to_string(targetPlayerPres->getMinerals()) + " / " + std::to_string(targetPlayerPres->getMineralCap()) + "\n" + \
                            "Energy: " + std::to_string(targetPlayerPres->getEnergy()) ;
        }
    }

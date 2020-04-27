#ifndef PLAYERGUI_H
#define PLAYERGUI_H
#include <vector>
#include <string>
#include "TestGUI.h"
class Player;
class PlayerPresence;
namespace PlayerGUI
{
    void sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative, Player* targetPlayer);
    void sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative, PlayerPresence* targetPlayerPres);

    void descPlayer(Player* targetPlayer, std::string& resultString);
    void descPlayerPres(PlayerPresence* targetPlayerPres, std::string& resultString);


    template<typename T>
    T& menu(std::vector<std::pair<std::string,T>>& options, Player* targetPlayer);

    template<typename T>
    T& menu(std::vector<std::pair<std::string,T>>& options, PlayerPresence* targetPlayerPres);
}
#endif // PLAYERGUI_H

template<typename T>
T& PlayerGUI::menu(std::vector<std::pair<std::string,T>>& options, Player* targetPlayer)
{
    std::string desc;
    descPlayer(targetPlayer,desc);
    return TestGUI::menu(options,desc);
}

template<typename T>
T& PlayerGUI::menu(std::vector<std::pair<std::string,T>>& options, PlayerPresence* targetPlayerPres)
{
    std::string desc;
    descPlayerPres(targetPlayerPres,desc);
    return TestGUI::menu(options,desc);
}

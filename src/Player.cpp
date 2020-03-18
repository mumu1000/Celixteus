#include "Player.h"
#include <iostream>
Player::Player()
{
        std::cout << "Player Created\n";
}

Player::~Player()
{
        std::cout << "Player Destroyed\n";
}


void Player::registerPlayerPresence(PlayerPresence* playerPresence)
{
    m_playerPresenceList.push_back(playerPresence);
}

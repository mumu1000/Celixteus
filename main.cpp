#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include <random>
#include <atomic>
#include "Existence.h"
#include "ExistenceView.h"
#include "Planet.h"
#include "PlanetView.h"
#include "Universe.h"
#include "UniverseView.h"
#include "SuperCluster.h"
#include "Cluster.h"
#include "Galaxy.h"
#include "SolarSys.h"
#include <ctime>
#include "Player.h"
#include "TestGUI.h"
#include "PlayerGUI.h"

int main(int argc, char **argv)
{
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    srand(now_ms.time_since_epoch().count());


    TestGUI::initialize();

    std::vector<std::pair<std::string,int>> options;
    for (int i = 0; i<=1000; i++)
    {
        std::string temp1 = "Choice " + std::to_string(i);
        options.push_back(std::make_pair(temp1,i));
    }

    TestGUI::sliders(options, false);
    TestGUI::menu(options);
    Existence& testExistence = *(new Existence());
    int player = testExistence.newPlayer();
    testExistence.genUniverse(player);
    testExistence[0].genSuperCluster(player,0);
    testExistence[0][0].genCluster(player,0);
    testExistence[0][0][0].genGalaxy(player,0);
    testExistence[0][0][0][0].genSolarSys(player,0);
    testExistence[0][0][0][0][0].genPlanet(player,0);


    //PlanetView* testPlanetView = new PlanetView(&(testExistence[0][0][0][0][0][0]),player,true);
    ExistenceView* testExistenceview = new ExistenceView(&testExistence,player,true);
    TestGUI::enterGUI(testExistenceview);

    TestGUI::shutDown();

    return 0;
}

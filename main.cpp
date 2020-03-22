#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include <random>
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

int main(int argc, char **argv)
{
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    srand(now_ms.time_since_epoch().count());
    //ALLEGRO_FONT* basicFont = al_create_builtin_font();
    //ALLEGRO_COLOR basicTextColor = al_map_rgb(255,255,255);
    //ALLEGRO_EVENT_QUEUE * keyboardEventQueue = al_create_event_queue();
    //ALLEGRO_EVENT keyboardEvent;
    //al_register_event_source(keyboardEventQueue,al_get_keyboard_event_source());

    //al_set_new_window_position(0,0);
    //al_set_new_display_flags(ALLEGRO_FRAMELESS);
    //ALLEGRO_DISPLAY * alConcreteDisplay = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);


    TestGUI::initialize();
/*
    std::vector<std::string> choices;
    choices.push_back("choice 1");
    choices.push_back("choice 2");
    choices.push_back("choice 3");
    choices.push_back("Return");
    unsigned int menuResult = TestGUI::menu(choices);
    std::cout << "You chose option " << menuResult << " : " << choices[menuResult] << "\n";
*/


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


    PlanetView* testPlanetView = new PlanetView(&(testExistence[0][0][0][0][0][0]),player,true);
    TestGUI::enterGUI(testPlanetView);
    //delete testExistence;

    TestGUI::shutDown();
    //al_destroy_display(alConcreteDisplay);

    return 0;
}

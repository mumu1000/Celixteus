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
#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080
#include "Existence.h"
#include "ExistenceView.h"
#include "Planet.h"
#include "PlanetView.h"
#include "UniverseView.h"
#include <ctime>
#include "Player.h"

int main(int argc, char **argv)
{
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    srand(now_ms.time_since_epoch().count());
    if (al_init() && al_init_primitives_addon() && al_init_font_addon())
    {
        std::cout<<"It Works\n";
    }else
    {
        std::cout << "Allegro Not Loaded\n";
        return 0x50000001;
    }
    if(!al_install_keyboard())
    {
        std::cout<<"Keyboard Installation Failed\n";
        return 0x50000002;
    }
    //ALLEGRO_FONT* basicFont = al_create_builtin_font();
    //ALLEGRO_COLOR basicTextColor = al_map_rgb(255,255,255);
    //ALLEGRO_EVENT_QUEUE * keyboardEventQueue = al_create_event_queue();
    //ALLEGRO_EVENT keyboardEvent;
    //al_register_event_source(keyboardEventQueue,al_get_keyboard_event_source());

    //al_set_new_window_position(0,0);
    //al_set_new_display_flags(ALLEGRO_FRAMELESS);
    //ALLEGRO_DISPLAY * alConcreteDisplay = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);





    Player* testPlayer = new Player();
    Existence* testExistence = new Existence();
    testExistence->genUniverse(testPlayer);
    testExistence->genUniverse(testPlayer);

    ExistenceView* testExistenceView = new ExistenceView(testExistence);
    testExistenceView->draw();
    delete testExistence;



    al_set_target_bitmap(nullptr);
    //al_destroy_display(alConcreteDisplay);
    al_shutdown_primitives_addon();
    al_shutdown_font_addon();
    return 0;
}
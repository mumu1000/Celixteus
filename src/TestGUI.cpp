#include "TestGUI.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "AbstractView.h"


void TestGUI::info(std::string& toDisplay)
{
    using namespace TestGUI;
    al_clear_to_color(al_map_rgb(0,0,20));
    al_draw_multiline_text(basicFont,basicTextColor, 20, 20, DISPLAY_WIDTH - 40,fontHeight + linePadding, 0,toDisplay.c_str());
    al_flip_display();
    ALLEGRO_EVENT inputRecv;
    do
    {
        inputRecv =waitInput();
    }
    while(!(inputRecv.type == ALLEGRO_EVENT_KEY_DOWN && inputRecv.keyboard.keycode == keyConfig->find("VALIDATE")->second ) && !(inputRecv.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN));
}


bool TestGUI::initialize()
{
    if (al_init() && al_init_primitives_addon() && al_init_font_addon() && al_init_ttf_addon())
    {
        std::cout<<"It Works\n";
    }else
    {
        std::cout << "Allegro Not Loaded\n";
        exit(0x50000001);
    }
    if(!al_install_keyboard())
    {
        std::cout<<"Keyboard Installation Failed\n";
        exit(0x50000002);
    }
    if(!al_install_mouse())
    {
        std::cout<<"Mouse Installation Failed\n";
        exit(0x50000003);
    }
    using namespace TestGUI;
    basicFont = al_load_ttf_font("./FFF_Tusj.ttf",20,0);
    fontHeight = al_get_font_line_height(basicFont);
    linePadding = 0;
    basicTextColor = al_map_rgb(255,255,255);
    mainEventQueue = al_create_event_queue();
    al_register_event_source(mainEventQueue,al_get_keyboard_event_source());
    al_register_event_source(mainEventQueue,al_get_mouse_event_source());
    al_set_new_window_position(0,0);
    al_set_new_display_flags(ALLEGRO_FRAMELESS+ALLEGRO_FULLSCREEN_WINDOW);
    alConcreteDisplay = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);
    //al_grab_mouse(alConcreteDisplay);

    keyConfig = new std::unordered_map<std::string, int>;

    (*keyConfig)["UP"] = 0;
    (*keyConfig)["DOWN"] = 0;
    (*keyConfig)["VALIDATE"] = 0;


    std::unordered_map<std::string, int>::iterator itr;
    for (itr = (*keyConfig).begin(); itr != (*keyConfig).end(); itr++)
    {
        al_clear_to_color(al_map_rgb(0,0,20));
        std::cout << itr->first <<" : ";
        std::string toBeWritten("Please Input a ::"+ itr->first +":: Key.");
        al_draw_text(basicFont,basicTextColor,20,20,0,&toBeWritten[0]);
        al_flip_display();
        itr->second = waitKeyboardInput();
        std::cout << itr->second << "\n";
        std::cout << "on to the next\n";
    }

    return true;
}



void TestGUI::enterGUI(AbstractView* enteringView)
{
    AbstractView* currentView = enteringView;
    while (currentView != nullptr)
    {
        AbstractView* nextView = currentView->draw();
        if (nextView !=currentView)
        {
            delete currentView;
        }
        currentView = nextView;
    }
}



bool TestGUI::shutDown()
{
    using namespace TestGUI;
    //al_ungrab_mouse();
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_destroy_display(alConcreteDisplay);
    al_destroy_font(basicFont);
    al_destroy_event_queue(mainEventQueue);
    al_set_target_bitmap(nullptr);
    al_shutdown_primitives_addon();
    al_shutdown_font_addon();
    delete keyConfig;
    return true;
}

ALLEGRO_EVENT TestGUI::waitInput()
{
    using namespace TestGUI;
    ALLEGRO_EVENT inputEvent;
    do{al_wait_for_event(mainEventQueue,&inputEvent);}while( !(inputEvent.type == ALLEGRO_EVENT_KEY_DOWN || (inputEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && inputEvent.mouse.display == alConcreteDisplay)));
    return inputEvent;
}

int TestGUI::waitKeyboardInput()
{
    using namespace TestGUI;
    ALLEGRO_EVENT inputEvent;
    do{al_wait_for_event(mainEventQueue,&inputEvent);}while( inputEvent.type != ALLEGRO_EVENT_KEY_DOWN);
    return inputEvent.keyboard.keycode;
}







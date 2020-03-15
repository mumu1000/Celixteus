#include "TestGUI.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include <iostream>
#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080

unsigned int TestGUI::menu(std::vector<std::string>& options)
{
    using namespace TestGUI;
    unsigned int current = 0;
    unsigned int maxperscreen = (DISPLAY_HEIGHT-10) / (fontHeight * 1.4);
    unsigned int lbegin = current - (current%maxperscreen);
    unsigned int lend = maxperscreen + current - (current%maxperscreen);
    al_clear_to_color(al_map_rgb(0,0,20));
    for (unsigned int i = lbegin; i<options.size() || i<lend ;i++)
    {
        al_draw_text(basicFont,basicTextColor, 5, 5+(i*fontHeight * 1.4), 0,const_cast<char*>(options[i].c_str()));
    }
}

bool TestGUI::initialize()
{
    if (al_init() && al_init_primitives_addon() && al_init_font_addon())
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

    using namespace TestGUI;
    basicFont = al_create_builtin_font();
    fontHeight = 8;
    basicTextColor = al_map_rgb(255,255,255);
    keyboardEventQueue = al_create_event_queue();
    al_register_event_source(keyboardEventQueue,al_get_keyboard_event_source());
    al_set_new_window_position(0,0);
    al_set_new_display_flags(ALLEGRO_FRAMELESS);
    alConcreteDisplay = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);

    keyNames = new std::vector<std::string>;
    keyConfig = new std::vector<int>;

    keyNames->push_back(std::string("UP"));
    keyNames->push_back(std::string("DOWN"));
    keyNames->push_back(std::string("VALIDATE"));


    for(unsigned int i = 0;i<keyNames->size();i++)
    {
        al_clear_to_color(al_map_rgb(0,0,20));
        std::cout<<(*keyNames)[i]<<" : ";
        std::string toBeWritten("Please Input a ::"+(*keyNames)[i]+":: Key.");
        al_draw_text(basicFont,basicTextColor,20,20,0,&toBeWritten[0]);
        al_flip_display();
        ALLEGRO_EVENT keyboardEvent;
        do{al_wait_for_event(keyboardEventQueue,&keyboardEvent);}while( keyboardEvent.type != ALLEGRO_EVENT_KEY_DOWN);
        keyConfig->push_back(keyboardEvent.keyboard.keycode);
        std::cout << (*keyConfig)[i] << "  \n";
        std::cout << "on to the next \n";
    }

    return true;
}

bool TestGUI::shutDown()
{
    using namespace TestGUI;
    al_destroy_display(alConcreteDisplay);
    al_destroy_font(basicFont);
    al_destroy_event_queue(keyboardEventQueue);
    al_set_target_bitmap(nullptr);
    delete keyNames;
    delete keyConfig;
    return true;
}










#include "TestGUI.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include <iostream>
#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080

unsigned int TestGUI::menu(std::vector<std::pair<std::string,unsigned int>>& options)
{
    using namespace TestGUI;
    int lastKey;
    unsigned int current = 0;
    unsigned int maxperscreen = (DISPLAY_HEIGHT-40) / (fontHeight * 1.4);
    unsigned int lbegin = current - (current%maxperscreen);
    unsigned int lend = maxperscreen + current - (current%maxperscreen);
    do {
        al_clear_to_color(al_map_rgb(0,0,20));
        for (unsigned int i = lbegin; i<options.size() && i<lend ;i++)
        {
            if (i == current) {al_draw_filled_circle(10,(20+(fontHeight/2)+(i*fontHeight * 1.4)),5,basicTextColor);}
            al_draw_text(basicFont,basicTextColor, 20, 20+(i*fontHeight * 1.4), 0,options[i].first.c_str());
        }
        al_flip_display();
        lastKey = waitKeyPress();
        if (lastKey == keyConfig->find("UP")->second)
        {
            if (current == 0)
            {
                current = options.size();
            }
            current--;
        }
        if (lastKey == keyConfig->find("DOWN")->second)
        {
            current++;
            if (current == options.size())
            {
                current = 0;
            }
        }
    }while(lastKey != keyConfig->find("VALIDATE")->second );
    return options[current].second;
}


void TestGUI::info(std::string& toDisplay)
{
    using namespace TestGUI;
    al_clear_to_color(al_map_rgb(0,0,20));
    al_draw_multiline_text(basicFont,basicTextColor, 20, 20, DISPLAY_WIDTH - 40,fontHeight * 1.4, 0,toDisplay.c_str());
    al_flip_display();
    while(waitKeyPress() != keyConfig->find("VALIDATE")->second ) {}
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
    fontHeight = al_get_font_line_height(basicFont);
    basicTextColor = al_map_rgb(255,255,255);
    keyboardEventQueue = al_create_event_queue();
    al_register_event_source(keyboardEventQueue,al_get_keyboard_event_source());
    al_set_new_window_position(0,0);
    al_set_new_display_flags(ALLEGRO_FRAMELESS);
    alConcreteDisplay = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);

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
        itr->second = waitKeyPress();
        std::cout << itr->second << "\n";
        std::cout << "on to the next\n";
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
    delete keyConfig;
    return true;
}

int TestGUI::waitKeyPress()
{
    using namespace TestGUI;
    ALLEGRO_EVENT keyboardEvent;
    do{al_wait_for_event(keyboardEventQueue,&keyboardEvent);}while( keyboardEvent.type != ALLEGRO_EVENT_KEY_DOWN);
    return keyboardEvent.keyboard.keycode;
}









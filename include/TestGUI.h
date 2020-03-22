#ifndef TESTGUI_H
#define TESTGUI_H
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
class AbstractView;
namespace TestGUI
{
    void info(std::string& toDisplay);
    bool initialize();
    void enterGUI(AbstractView* enteringView);
    bool shutDown();
    ALLEGRO_DISPLAY* alConcreteDisplay;
    ALLEGRO_FONT* basicFont;
    ALLEGRO_COLOR basicTextColor;
    ALLEGRO_EVENT_QUEUE* mainEventQueue;
    std::unordered_map<std::string, int>* keyConfig;
    unsigned int fontHeight;
    unsigned int linePadding = 0;
    unsigned int sliderHorPadd = 2;
    ALLEGRO_EVENT waitInput();
    int waitKeyboardInput();
    unsigned int DISPLAY_WIDTH = 1920;
    unsigned int DISPLAY_HEIGHT = 1080;

    void sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative);


    template<typename T>
    T& menu(std::vector<std::pair<std::string,T>>& options);

}

template<typename T>
T& TestGUI::menu(std::vector<std::pair<std::string,T>>& options)
{
    using namespace TestGUI;
    bool validate = false;
    ALLEGRO_EVENT inputEvent;
    unsigned int current = 0;
    const unsigned int maxperscreen = (DISPLAY_HEIGHT-40) / (fontHeight + linePadding);

    do {
        unsigned int lbegin = current - (current%maxperscreen);
        unsigned int offset = current-(current%maxperscreen);
        unsigned int lend = maxperscreen + current - (current%maxperscreen);
        al_clear_to_color(al_map_rgb(0,0,20));
        for (unsigned int i = lbegin; i<options.size() && i<lend ;i++)
        {
            if (i == current) {al_draw_filled_circle(10,(20+(fontHeight/2)+((i-offset)*(fontHeight + linePadding))),5,basicTextColor);}
            al_draw_text(basicFont,basicTextColor, 20, 20+((i-offset)*(fontHeight + linePadding)), 0,options[i].first.c_str());
        }
        if (lbegin != 0){ al_draw_filled_triangle(5, 13, 15, 13, 10, 5, basicTextColor) ;}
        if (lend < options.size()-1){ al_draw_filled_triangle(5, DISPLAY_HEIGHT - 13, 15, DISPLAY_HEIGHT - 13, 10, DISPLAY_HEIGHT - 5, basicTextColor) ;}


        al_flip_display();
        inputEvent = waitInput();
        if (inputEvent.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            int lastKey = inputEvent.keyboard.keycode;
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
            if (lastKey == keyConfig->find("VALIDATE")->second)
            {
                validate = true;
            }
        }
        if (inputEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int yClicked = inputEvent.mouse.y;
            unsigned int itemClicked = ((yClicked-20) / (fontHeight + linePadding))+offset;
            if (yClicked >= 20 && yClicked < (int)(20+(maxperscreen*(fontHeight + linePadding))) && itemClicked >= 0 && itemClicked < options.size()){current = itemClicked;validate = true; }
            if (yClicked < 20 && lbegin != 0){current = offset-1;}
            if (yClicked >= (int)(20+(maxperscreen*(fontHeight + linePadding))) && lend < options.size()-1){current = offset+maxperscreen;}
        }
    }while(!validate);
    return options[current].second;
}




#endif // MENU_H

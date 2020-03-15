#ifndef TESTGUI_H
#define TESTGUI_H
#include <vector>
#include <string>
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
namespace TestGUI
{
    unsigned int menu(std::vector<std::string>& options);
    bool initialize();
    bool shutDown();
    ALLEGRO_DISPLAY* alConcreteDisplay;
    ALLEGRO_FONT* basicFont;
    ALLEGRO_COLOR basicTextColor;
    ALLEGRO_EVENT_QUEUE* keyboardEventQueue;
    std::vector<int>* keyConfig;
    std::vector<std::string>* keyNames;
    unsigned int fontHeight;
}


#endif // MENU_H

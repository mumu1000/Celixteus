#ifndef TESTGUI_H
#define TESTGUI_H
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
    unsigned int menu(std::vector<std::pair<std::string,unsigned int>>& options);
    void info(std::string& toDisplay);
    bool initialize();
    void enterGUI(AbstractView* enteringView);
    bool shutDown();
    ALLEGRO_DISPLAY* alConcreteDisplay;
    ALLEGRO_FONT* basicFont;
    ALLEGRO_COLOR basicTextColor;
    ALLEGRO_EVENT_QUEUE* keyboardEventQueue;
    std::unordered_map<std::string, int>* keyConfig;
    unsigned int fontHeight;
    int waitKeyPress();
}


#endif // MENU_H

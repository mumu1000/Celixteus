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

    void* startMusic(void* args);
    unsigned int DISPLAY_WIDTH = 1920;
    unsigned int DISPLAY_HEIGHT = 1080;

    void sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative);
    void sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative, const std::string& headerStr);
    void sliders(std::vector<std::pair<std::string,int>>& options, unsigned int& startpos, bool canBeNegative);
    void sliders(std::vector<std::pair<std::string,int>>& options, unsigned int& startpos, bool canBeNegative, const std::string& headerStr);

    template<typename T>
    T& menu(std::vector<std::pair<std::string,T>>& options);

    template<typename T>
    T& menu(std::vector<std::pair<std::string,T>>& options, const std::string& headerStr);

    template<typename T>
    T& menu(std::vector<std::pair<std::string,T>>& options, unsigned int& startpos);

    template<typename T>
    T& menu(std::vector<std::pair<std::string,T>>& options, unsigned int& startpos, const std::string& headerStr);

}

template<typename T>
T& TestGUI::menu(std::vector<std::pair<std::string,T>>& options)
{
    const std::string emptyString = "";
    unsigned int startpos = 0;
    return TestGUI::menu(options,startpos,emptyString);
}

template<typename T>
T& TestGUI::menu(std::vector<std::pair<std::string,T>>& options, const std::string& headerStr)
{
    unsigned int startpos = 0;
    return TestGUI::menu(options,startpos,headerStr);
}

template<typename T>
T& TestGUI::menu(std::vector<std::pair<std::string,T>>& options, unsigned int& startpos)
{
    const std::string emptyString = "";
    return TestGUI::menu(options,startpos,emptyString);
}

template<typename T>
T& TestGUI::menu(std::vector<std::pair<std::string,T>>& options, unsigned int& startpos, const std::string& headerStr)
{
    using namespace TestGUI;
    unsigned int menuHeigth = DISPLAY_HEIGHT;
    const unsigned int textHeaderHeight = linePadding;
    if (headerStr != "")  //Calculating Text Header Height Here
    {
        al_do_multiline_text
        (
            basicFont ,    // Our font
            (DISPLAY_WIDTH - 40) , // Padded Screen Width
            headerStr.c_str() , // Our text header
            [](int line_num , const char* line , int size , void* extra)
            {
                unsigned int* currHeight = (unsigned int*)extra; // We use the "extra" value to get our counter in the lambda function
                (*currHeight)+= (fontHeight + linePadding); // For each line we increment the counter by one padded line height
                return true;
            }, // A counter Lambda function
            (void*)&textHeaderHeight             // We need to pass a counter value to increment
        );
    }
    const unsigned int goDownHeaderHeight = 20;
    const unsigned int goUpHeaderHeight = 20;
    const unsigned int headerHeight = goDownHeaderHeight+textHeaderHeight;
    const unsigned int footerHeight = goUpHeaderHeight;
    //Handle headerHeightCalcsHere
    if (menuHeigth < ((fontHeight + linePadding) + headerHeight + footerHeight))  // Need 1 lines at least + headers, if we dont this menu cant work
    {
        std::cerr << "Font too big to display any menu. Please report to Dev\n EXITING\n"; //WE MUST HANDLE THIS BEFORE AND THIS SHOULD NEVER HAPPEN
        exit(0x50000003);
    }
    menuHeigth -= headerHeight;
    menuHeigth -= footerHeight;
    bool validate = false;
    ALLEGRO_EVENT inputEvent;
    unsigned int& current = startpos;
    current = startpos-startpos*(!(startpos<options.size()));
    const unsigned int maxperscreen = (menuHeigth) / (fontHeight + linePadding);

    do {
        unsigned int lbegin = current - (current%maxperscreen);
        unsigned int offset = current-(current%maxperscreen);
        unsigned int lend = maxperscreen + current - (current%maxperscreen);
        al_clear_to_color(al_map_rgb(0,0,20));
        if (headerStr != "")
        {
            al_draw_multiline_text(basicFont,basicTextColor, 20, linePadding,(DISPLAY_WIDTH - 40),(fontHeight + linePadding), 0,headerStr.c_str());
        }
        for (unsigned int i = lbegin; i<options.size() && i<lend ;i++)
        {
            if (i == current) {al_draw_filled_circle(10,(headerHeight+(fontHeight/2)+((i-offset)*(fontHeight + linePadding))),5,basicTextColor);}
            al_draw_text(basicFont,basicTextColor, 20, headerHeight+((i-offset)*(fontHeight + linePadding)), 0,options[i].first.c_str());
        }
        if (lbegin != 0  || lend < options.size()-1)
        {
            al_draw_filled_triangle(5, (headerHeight - goDownHeaderHeight) + 13, 15, (headerHeight - goDownHeaderHeight) + 13, 10, (headerHeight - goDownHeaderHeight) + 5, basicTextColor);
            al_draw_filled_triangle(5, headerHeight + menuHeigth + footerHeight - 13, 15, headerHeight + menuHeigth + footerHeight - 13, 10, headerHeight + menuHeigth + footerHeight - 5, basicTextColor) ;
        }


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
            int yBegin = headerHeight;
            int yEnd = yBegin + menuHeigth;
            unsigned int itemClicked = ((yClicked-yBegin) / (fontHeight + linePadding))+offset;
            if (yClicked >= yBegin && yClicked < yEnd && itemClicked >= 0 && itemClicked < options.size())
            {
                current = itemClicked;
                validate = true;
            }
            if ((unsigned int)yClicked < headerHeight && (unsigned int)yClicked >= textHeaderHeight && (lbegin != 0 || lend < options.size()-1))
            {
                if (lbegin == 0)
                {
                    current = options.size()-1;
                }
                else
                {
                    current = offset -1;
                }
            }
            if (yClicked >= yEnd && (lbegin != 0 || lend < options.size()-1))
            {
                if (lend >= options.size()-1)
                {
                    current = 0;
                }
                else
                {
                    current = offset+maxperscreen;
                }
            }
        }
    }while(!validate);
    return options[current].second;
}




#endif // TESTGUI_H

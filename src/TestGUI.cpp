#include "TestGUI.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "AbstractView.h"





bool TestGUI::initialize()
{
    if (al_init() && al_init_primitives_addon() && al_init_font_addon() && al_init_ttf_addon())
    {
        std::cout<<"It Works\n";
    }else
    {
        std::cerr << "Allegro Not Loaded\n";
        exit(0x50000001);
    }
    if(!al_install_keyboard())
    {
        std::cerr<<"Keyboard Installation Failed\n";
        exit(0x50000002);
    }
    if(!al_install_mouse())
    {
        std::cerr<<"Mouse Installation Failed\n";
        exit(0x50000003);
    }
    using namespace TestGUI;
    basicFont = al_load_ttf_font("./FFF_Tusj.ttf",20,0);
    fontHeight = al_get_font_line_height(basicFont);
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
    (*keyConfig)["LEFT"] = 0;
    (*keyConfig)["RIGHT"] = 0;
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

void TestGUI::sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative)
{
    const std::string emptyString = "";
    return TestGUI::sliders(options,canBeNegative,emptyString);
}

void TestGUI::sliders(std::vector<std::pair<std::string,int>>& options, bool canBeNegative, const std::string& headerStr)
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
    if (menuHeigth < ((fontHeight + linePadding)*2 + headerHeight + footerHeight))  // Need 2 lines at least + headers, if we dont this menu cant work
    {
        std::cerr << "Font too big to display any menu. Please report to Dev\n EXITING\n"; //WE MUST HANDLE THIS BEFORE AND THIS SHOULD NEVER HAPPEN
        exit(0x50000003);
    }
    menuHeigth -= headerHeight;
    menuHeigth -= footerHeight;
    bool validate = false;
    ALLEGRO_EVENT inputEvent;
    unsigned int current = 0;
    const unsigned int maxperscreen = menuHeigth / (fontHeight + linePadding) -1; //-1 to fit the validate option
    do {
        unsigned int lbegin = current - (current%maxperscreen);
        unsigned int offset = current-(current%maxperscreen);
        unsigned int lend = maxperscreen + current - (current%maxperscreen);
        al_clear_to_color(al_map_rgb(0,0,20));
        if (headerStr != "")
        {
            al_draw_multiline_text(basicFont,basicTextColor, 20, linePadding,(DISPLAY_WIDTH - 40),(fontHeight + linePadding), 0,headerStr.c_str());
        }
        al_draw_text(basicFont,basicTextColor, 20, headerHeight, 0,"Click Here or Press :VALIDATE: to Validate.");
        for (unsigned int i = lbegin; i<options.size() && i<lend ;i++)
        {
            unsigned int vertPos = headerHeight+((i-offset+1)*(fontHeight + linePadding)); //The +1 is to fit the validate Option
            if (i == current) {al_draw_filled_circle(10,vertPos+(fontHeight/2),5,basicTextColor);}
            unsigned int horPadding = 20;
            if( canBeNegative || options[i].second > 0)
            {
                al_draw_text(basicFont,basicTextColor, horPadding, vertPos, 0,"<");
            }
            horPadding += al_get_text_width(basicFont,"<")+sliderHorPadd;
            std::string number = std::to_string(options[i].second);
            al_draw_text(basicFont,basicTextColor, horPadding, vertPos, 0,number.c_str());
            horPadding += al_get_text_width(basicFont,number.c_str())+sliderHorPadd;
            al_draw_text(basicFont,basicTextColor, horPadding, vertPos, 0,">");
            horPadding += al_get_text_width(basicFont,">")+sliderHorPadd;

            al_draw_text(basicFont,basicTextColor, horPadding, vertPos, 0,options[i].first.c_str());
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
            if (lastKey == keyConfig->find("LEFT")->second)
            {
                if( canBeNegative || options[current].second > 0)
                {
                    options[current].second--;
                }
            }
            if (lastKey == keyConfig->find("RIGHT")->second)
            {
                options[current].second++;
            }
            if (lastKey == keyConfig->find("VALIDATE")->second)
            {
                validate = true;
            }
        }
        if (inputEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int yClicked = inputEvent.mouse.y;
            int xClicked = inputEvent.mouse.x;
            int yBegin = headerHeight+fontHeight+linePadding;
            int yEnd = yBegin + (maxperscreen*(fontHeight + linePadding));
            unsigned int itemClicked = ((yClicked-yBegin) / (fontHeight + linePadding))+offset;
            if (yClicked >= yBegin && yClicked < yEnd && itemClicked >= 0 && itemClicked < options.size())
            {
                current = itemClicked;
                const int minusMinX = 20;
                const int minusMaxX = minusMinX + al_get_text_width(basicFont,"<");
                const std::string number = std::to_string(options[current].second);
                const int plusMinX = minusMaxX + 2*sliderHorPadd + al_get_text_width(basicFont,number.c_str());
                const int plusMaxX = plusMinX + al_get_text_width(basicFont,">");
                if (xClicked >= minusMinX && xClicked < minusMaxX)
                {
                    if( canBeNegative || options[current].second > 0)
                    {
                        options[current].second--;
                    }
                }
                if (xClicked >= plusMinX && xClicked < plusMaxX)
                {
                    options[current].second++;
                }
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
            if ((unsigned int)yClicked >= headerHeight && yClicked < yBegin){validate=true;}
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







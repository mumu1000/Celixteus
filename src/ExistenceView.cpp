#include "ExistenceView.h"
#include "TestGUI.h"

ExistenceView::ExistenceView(Existence* targetExistence)
{
    m_targetExistence = targetExistence;
    m_xOrigin = 0.0;
    m_yOrigin = 0.0;
    m_zoom = 0.0;
}

ExistenceView::~ExistenceView()
{
    //dtor
}

void ExistenceView::draw()
{
    using namespace TestGUI;
    if (m_targetExistence == nullptr)
    {
        std::string towrite = "Broken Existence View: Pointed existence is nullptr\nReturning.";
        info(towrite);
        return;
    }
    std::vector<std::string> options;
    options.push_back("Generate Universe");
    options.push_back("List Universes");
    options.push_back("Goto Universe");
    options.push_back("Return to Player View (not implemented)");
    unsigned int response = menu(options);
    switch(response)
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;

    }

}

#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H


 class AbstractView
{
    public:
        AbstractView();
        virtual ~AbstractView();
        virtual AbstractView* draw() = 0;
    protected:

    private:
};

#endif // ABSTRACTVIEW_H

#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H


 class AbstractView
{
    public:
        AbstractView();
        virtual ~AbstractView();
        virtual void draw() = 0;
    protected:

    private:
};

#endif // ABSTRACTVIEW_H

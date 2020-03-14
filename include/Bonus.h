#ifndef BONUS_H
#define BONUS_H


class Bonus
{
    public:
        Bonus();
        virtual ~Bonus();

    protected:
        float m_constructionTimeFactor;
        float m_constructionResourceFactor;
        float m_productionSpeedFactor;
        float m_storageFactor;
    private:
};

#endif // BONUS_H

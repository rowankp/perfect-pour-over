#include "brewsuggestion.h"
#include <QtGlobal>

BrewSuggestion::BrewSuggestion()
{ }

QString BrewSuggestion::age(int a)
{
    QString ret;

    if (a < 4)
    {
        ret = "Beans may be too young.";
        _age = AGE::Young;
    }
    else if (a > 14)
    {
        ret = "Beans may be too old.";
        _age = AGE::Old;
    }
    else
        ret = "Beans are a good age.";

    return ret;
}

QString BrewSuggestion::grind(int g)
{
    QString ret;

    if (g > 3)
    {
        ret = "Grind may be too fine.";
        _grind = GRIND::Fine;
    }
    else if (g == 1)
    {
        ret = "Grind may be too coarse.";
        _grind = GRIND::Coarse;
    }
    else
        ret = "Grind seems to be on point.";

    return ret;
}

QString BrewSuggestion::brewRatio(double dosage, double water)
{
    int ratio = qRound(water) / qRound(dosage);
    _ratio = QString("1:%1 coffee to water").arg(ratio);

    if (ratio > 18)
        _ratioFlag = RATIO::Over;
    else if (ratio < 16)
        _ratioFlag = RATIO::Under;

     return _ratio;
}

QString BrewSuggestion::time(double t)
{
    QString ret;
    int mins = t / 60;

    if (mins > 7)
    {
        ret = "Brew time may be too long.";
        _time = TIME::Long;
    }
    else if (mins < 4)
    {
        ret = "Brew time may be too short";
        _time = TIME::Short;
    }
    else
        ret = "Brew time looks great.";

    return ret;
}

QString BrewSuggestion::temperature(double t)
{
    QString ret;

    if (t > 190)
    {
        ret = "Coffee may be too hot.";
        _temperature = TEMPERATURE::Hot;
    }
    else if (t < 175)
    {
        ret = "Coffee may be too cold.";
        _temperature = TEMPERATURE::Cold;
    }
    else
        ret = "Temperature looks good.";

    return ret;
}

QString BrewSuggestion::acidity(double pH)
{
    QString ret;

    if (pH < 4.85)
    {
        ret = "Coffee is too acidic!";
        _pH = ACIDITY::Acidic;
    }
    else if (pH > 5.10)
    {
        ret = "Coffee is probably too watery.";
        _pH = ACIDITY::Watery;
    }
    else
        ret = "Acidity is in a good range.";

    return ret;
}

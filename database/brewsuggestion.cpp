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
    else if (g < 2)
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

    return _ratio + " ratio.";
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
    _temperature = QString("%1°F").arg(t);

    if (t > 190)
    {
        ret = "Coffee may be too hot.";
        _temperatureFlag = TEMPERATURE::Hot;
    }
    else if (t < 175)
    {
        ret = "Coffee may be too cold.";
        _temperatureFlag = TEMPERATURE::Cold;
    }
    else
        ret = "Temperature looks good.";

    return ret;
}

QString BrewSuggestion::acidity(double pH)
{
    QString ret;
    _ph = QString("%1").arg(pH);

    if (pH < 4.85)
    {
        ret = "Coffee is too acidic!";
        _phFlag = ACIDITY::Acidic;
    }
    else if (pH > 5.10)
    {
        ret = "Coffee is probably too watery.";
        _phFlag = ACIDITY::Watery;
    }
    else
        ret = "Acidity is in a good range.";

    return ret;
}

QString BrewSuggestion::summary()
{
    QString ret("For Better Brewing\n");

    switch(_age)
    {
        case AGE::Young:
            ret.append("\nAge: \n");
            ret.append("   - Consider letting your beans age a bit more. Beans are optimal between 4 and 14 days in age.\n");
            break;
        case AGE::Old:
            ret.append("\nAge: \n");
            ret.append("   - Your beans are old, consider buying new ones or adjusting your dosage.\n");
            ret.append("     Beans are optimal between 4 and 14 days in age.\n");
            break;
    }

    switch(_grind)
    {
        case GRIND::Fine:
            ret.append("\nGrind: \n");
            ret.append("   - If you coffee has a bitter, charred aftertaste and slow extraction time, consider a\n");
            ret.append("     coarser grind.\n");
            break;
        case GRIND::Coarse:
            ret.append("\nGrind: \n");
            ret.append("   - If you coffee has a sour taste and fast extraction time, consider a finer grind.\n");
            break;
    }

    switch(_ratioFlag)
    {
        case RATIO::Under:
            ret.append("\nBrew Ratio: \n");
            ret.append("   - If your coffee has washed out flavors, a thin watery body, or woody, filmly aftertaste, consider\n");
            ret.append("     adjusting your brewing ratio by increasing your dosage or decreasing your water amount.\n");
            ret.append(QString("     Your brewing ratio was %1. We recommend a brewing ratio of about 1:17\n").arg(_ratio));
            break;
        case RATIO::Over:
            ret.append("\nBrew Ratio: \n");
            ret.append("   - If your coffee has aggressive acidty, underdeveloped flavors, or a heavy body, consider\n");
            ret.append("     adjusting your brewing ratio by decreasing your dosage or increasing your water amount.\n");
            ret.append(QString("     Your brewing ratio was %1. We recommend a brewing ratio of about 1:17\n").arg(_ratio));
            break;
    }

    switch(_time)
    {
        case TIME::Short:
            ret.append("\nBrew Time: \n");
            ret.append("   - If your coffee has a sour, underdeveloped flavor and no mount feel, consider\n");
            ret.append("     increasing your brewing time. Optimal brewing time is between about 5-6 minutes.");
            break;
        case TIME::Long:
            ret.append("\nBrew Time: \n");
            ret.append("   - If your coffee has a bitter, muddled flavor and thin, \"diner coffee\" taste, consider\n");
            ret.append("     decreasing your brewing time. Optimal brewing time is between about 5-6 minutes.\n");
            break;
    }

    switch(_temperatureFlag)
    {
        case TEMPERATURE::Cold:
            ret.append("\nTemperature: \n");
            ret.append("   - Consider brewing with hotter water or keeping the water on heat while brewing.\n");
            ret.append(QString("     Your coffee temperature was %1. Optimal water temperature is between 175°F and 190°F.\n").arg(_temperatureFlag));
            break;
        case TEMPERATURE::Hot:
            ret.append("\nTemperature: \n");
            ret.append("   - Consider brewing with cooler water, you may be scalding your beans.\n");
            ret.append(QString("     Your coffee temperature was %1. Optimal water temperature is between 175°F and 190°F.\n").arg(_temperatureFlag));
            break;
    }

    switch(_phFlag)
    {
        case ACIDITY::Acidic:
            ret.append("\nAcidity: \n");
            ret.append("   - Your coffee is too acidic! Consider adusting your grind or brewing ratio. Your coffee pH\n");
            ret.append(QString("     was %1.The expected pH of coffee is between 4.85 and 5.10.").arg(_ph));
            break;
        case ACIDITY::Watery:
            ret.append("\nAcidity: \n");
            ret.append("   - Your coffee is too basic. Consider adusting your grind or brewing ratio. Your coffee pH\n");
            ret.append(QString("     was %1.The expected pH of coffee is between 4.85 and 5.10.").arg(_ph));
            break;
    }

    return ret;
}

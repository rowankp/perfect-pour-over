#ifndef BREWSUGGESTION_H
#define BREWSUGGESTION_H

#include "global.h"

#include <QString>

enum AGE { Young = -1, Old = 1};
enum GRIND { Fine = -1, Coarse = 1 };
enum TIME { Short = -1, Long = 1};
enum TEMPERATURE { Cold = -1, Hot = 1};
enum ACIDITY { Acidic = -1, Watery = 1};
enum RATIO { Under = -1, Over = 1};

class BrewSuggestion
{
    public:
        QString age(int a);
        QString grind(int g);
        QString brewRatio(double dosage, double water);
        QString time(double t);
        QString temperature(double t);
        QString acidity(double pH);

        static BrewSuggestion &suggestion() { static BrewSuggestion b; return b; }

    private:
        BrewSuggestion();

        int _age = 0;
        int _grind = 0;
        int _time = 0;
        int _temperature = 0;
        int _pH = 0;
        QString _ratio = "0:0";
        int _ratioFlag = 0;
};


#endif // BREWSUGGESTION_H

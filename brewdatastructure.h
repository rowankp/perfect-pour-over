#ifndef BREWDATASTRUCTURE_H
#define BREWDATASTRUCTURE_H

#include <QString>
#include <QDateTime>
#include <vector>
using std::vector;

#define ROAST_LIGHT         0
#define ROAST_MEDIUM_LIGHT  1
#define ROAST_MEDIUM        2
#define ROAST_MEDIUM_DARK   3
#define ROAST_DARK          4

struct BrewData
{
    int run_id = -1;
    QString run = "NULL";
    QString region = "NULL";
    int     roast = -1;
    int     age = -1;
    int     grind = -1;
    double  water = -1;
    double  dosage = -1;
    vector<double> temperature;
    vector<double> pH;
    QString brew_time = "NULL";
};

#endif // BREWDATASTRUCTURE_H

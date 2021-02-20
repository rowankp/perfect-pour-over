#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

#include "brewdatastructure.h"

class DatabaseManager
{
    public:
        DatabaseManager();
        ~DatabaseManager();

        bool addRun(BrewData &record);
        bool updateRecord(const BrewData &data);

    private:
        QSqlDatabase _database;

        bool newStaticRecord(const QString &timestamp);
        bool newTemperatureRecord(const QString &timestamp);
        bool newAcidityRecord(const QString &timestamp);
        bool updateTemperature(const BrewData &data);
        bool updateAcidity(const BrewData &data);
};

#endif // DATABASEMANAGER_H

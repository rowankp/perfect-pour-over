#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "brewdatastructure.h"

#include <QSqlDatabase>
#include <QString>
#include <vector>
using std::vector;

class DatabaseManager
{
    public:
        ~DatabaseManager();
        QSqlQuery query(QString q);
        QSqlQuery query(QString q, QString startDate, QString endDate);
        bool addRun(BrewData &record);
        bool updateRecord(const BrewData &data);
        vector<BrewData> getData();
        vector<BrewData> getData(QString startDate, QString endDate);
        BrewData getData(QString date);

        static DatabaseManager &database() { static DatabaseManager db; return db; }

    private:
        DatabaseManager();
        bool newStaticRecord(const QString &timestamp);
        bool newTemperatureRecord(const QString &timestamp);
        bool newAcidityRecord(const QString &timestamp);
        bool updateTemperature(const BrewData &data);
        bool updateAcidity(const BrewData &data);
        void getPhData(BrewData &data);
        void getTemperatureData(BrewData &data);
        BrewData convertToBrewData(const QSqlQuery &query);

        QSqlDatabase _database;
};

#endif // DATABASEMANAGER_H

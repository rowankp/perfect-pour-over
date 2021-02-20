#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DatabaseManager::DatabaseManager()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setDatabaseName("C:\\Users\\rowan\\OneDrive\\Documents\\OIT\\Senior Project\\perfect-pour-over\\database\\BrewData.db");
}

DatabaseManager::~DatabaseManager()
{ }

bool DatabaseManager::addRun(BrewData &record)
{
    bool success = false;

    if (_database.open())
    {
        if (newStaticRecord(record.run) && newAcidityRecord(record.run) && newTemperatureRecord(record.run))
        {
            QSqlQuery query(_database);

            if (query.exec(QString("SELECT RunId from StaticData WHERE BrewDate = '\%1'").arg(record.run)))
            {
                query.first();
                record.run_id = query.value(0).toInt();
                success = true;
            }
            else
            {
                qDebug() << "ERROR:DatabaseManager::addRun:" << query.lastError();
            }
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::addRun: unable to create new run";
        }

        _database.close();
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::addRun: unable to open database";
    }

    return success;
}

bool DatabaseManager::updateRecord(const BrewData &data)
{
    bool success = false;

    if (_database.open())
    {
        updateTemperature(data);
        updateAcidity(data);

        QString query("UPDATE StaticData SET ");
        query.append(QString("Region = '%1', ").arg(data.region));
        query.append(QString("Roast = %1, ").arg(data.roast));
        query.append(QString("Age = %1, ").arg(data.age));
        query.append(QString("Grind = %1, ").arg(data.grind));
        query.append(QString("Water = %1, ").arg(data.water));
        query.append(QString("Dosage = %1, ").arg(data.dosage));
        query.append(QString("BrewTime = '%1' ").arg(data.brew_time));
        query.append(QString("WHERE BrewDate = '%1'").arg(data.run));

        QSqlQuery updateQuery(_database);
        updateQuery.prepare(query);

        if(!updateQuery.exec())
            qDebug() << "ERROR:DatabaseManager::updateRecord:" << updateQuery.lastError();
        else
            success = true;

        _database.close();
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::updateRecord: unable to open database";
    }

    return success;
}

bool DatabaseManager::newStaticRecord(const QString &timestamp)
{
    bool success = false;

    if (_database.isOpen())
    {
        QSqlQuery query(_database);
        query.prepare("INSERT INTO StaticData (BrewDate) VALUES (:timestamp)");
        query.bindValue(":timestamp", timestamp);

        if(query.exec())
            success = true;
        else
            qDebug() << "ERROR:DatabaseManager::newStaticRecord:" << query.lastError();
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::newStaticRecord: database not open";
    }

    return success;
}

bool DatabaseManager::newTemperatureRecord(const QString &timestamp)
{
    bool success = false;

    if (_database.isOpen())
    {
        QSqlQuery query(_database);
        query.prepare("INSERT INTO TemperatureData (BrewDate) VALUES (:timestamp)");
        query.bindValue(":timestamp", timestamp);

        if(query.exec())
            success = true;
        else
            qDebug() << "ERROR:DatabaseManager::newTemperatureRecord:" << query.lastError();
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::newTemperatureRecord: database not open";
    }

    return success;
}

bool DatabaseManager::newAcidityRecord(const QString &timestamp)
{
    bool success = false;

    if (_database.isOpen())
    {
        QSqlQuery query(_database);
        query.prepare("INSERT INTO AcidityData (BrewDate) VALUES (:timestamp)");
        query.bindValue(":timestamp", timestamp);

        if(query.exec())
            success = true;
        else
            qDebug() << "ERROR:DatabaseManager::newAcidityRecord:" << query.lastError();
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::newAcidityRecord: database not open";
    }

    return success;
}

bool DatabaseManager::updateTemperature(const BrewData &data)
{
    bool success = false;

    if (_database.isOpen())
    {
        QSqlQuery updateQuery(_database);

        for (int ii = 0; ii < (int)data.temperature.size(); ++ii)
        {
            QString query("UPDATE TemperatureData SET ");
            query.append(QString("'%1' ").arg(ii));
            query.append(QString("= %1 ").arg(data.temperature.at(ii)));
            query.append(QString("WHERE RunId = %1").arg(data.run_id));

            updateQuery.prepare(query);

            if(!updateQuery.exec())
                qDebug() << "ERROR:DatabaseManager::updateTemperature:" << updateQuery.lastError();
        }

        success = true;
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::updateTemperature: unable to open database";
    }

    return success;
}

bool DatabaseManager::updateAcidity(const BrewData &data)
{
    bool success = false;

    if (_database.isOpen())
    {
        QSqlQuery updateQuery(_database);

        for (int ii = 0; ii < (int)data.pH.size(); ++ii)
        {
            QString query("UPDATE AcidityData SET ");
            query.append(QString("'%1' ").arg(ii));
            query.append(QString("= %1 ").arg(data.pH.at(ii)));
            query.append(QString("WHERE RunId = %1").arg(data.run_id));

            updateQuery.prepare(query);

            if(!updateQuery.exec())
                qDebug() << "ERROR:DatabaseManager::updateAcidity:" << updateQuery.lastError();
        }

        success = true;
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::updateAcidity: unable to open database";
    }

    return success;
}

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

QSqlQuery DatabaseManager::query(QString q)
{
    QSqlQuery query;

    if (_database.open())
    {
        if (!query.exec(q))
        {
            qDebug() << "ERROR:DatabaseManager::query:" << query.lastError();
            qDebug() << query.lastQuery();
        }
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::query: unable to open database";
    }

    _database.close();

    return query;
}

QSqlQuery DatabaseManager::query(QString q, QString startDate, QString endDate)
{
    QSqlQuery query;

    if (_database.open())
    {
        int startId = -1;
        int endId = -1;

        if (query.exec(QString("SELECT RunId from StaticData WHERE BrewDate LIKE '\%\%1\%'").arg(startDate)))
        {
            query.first();
            startId = query.value(0).toInt();
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::query:" << query.lastError();
            qDebug() << query.lastQuery();
            _database.close();
        }

        if (query.exec(QString("SELECT RunId from StaticData WHERE BrewDate LIKE '%\%1%'").arg(endDate)))
        {
            query.first();
            endId = query.value(0).toInt();
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::query:" << query.lastError();
            qDebug() << query.lastQuery();
            _database.close();
        }

        q.append(QString(" AND RunId BETWEEN %1 AND %2").arg(startId).arg(endId));

        if (!query.exec(q))
        {
            qDebug() << "ERROR:DatabaseManager::query:" << query.lastError();
            qDebug() << query.lastQuery();
        }

    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::query: unable to open database";
    }

    _database.close();

    return query;
}

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
        query.append(QString("BrewTime = '%1', ").arg(data.brew_time));
        query.append(QString("FinalAcidity = '%1', ").arg(data.pH.back()));
        query.append(QString("FinalTemperature = '%1', ").arg(data.temperature.back()));
        query.append(QString("Rating = '%1' ").arg(data.rating));
        query.append(QString("WHERE RunId = %1").arg(data.run_id));

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

vector<BrewData> DatabaseManager::getData()
{
    vector<BrewData> data;

    if (_database.open())
    {
        QSqlQuery query;

        if (query.exec(QString("SELECT * from StaticData")))
        {
            query.first();
            do { data.push_back(convertToBrewData(query)); }
            while (query.next());
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::getData:" << query.lastError();
            qDebug() << query.lastQuery();
        }

    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::getData: unable to open database";
    }

    _database.close();

    return data;
}

vector<BrewData> DatabaseManager::getData(QString startDate, QString endDate)
{
    vector<BrewData> data;

    if (_database.open())
    {
        QSqlQuery query;

        int startId = -1;
        int endId = -1;

        if (query.exec(QString("SELECT RunId from StaticData WHERE BrewDate LIKE '\%\%1\%'").arg(startDate)))
        {
            query.first();
            startId = query.value(0).toInt();
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::getData:" << query.lastError();
            qDebug() << query.lastQuery();
            _database.close();
            return data;
        }

        if (query.exec(QString("SELECT RunId from StaticData WHERE BrewDate LIKE '%\%1%'").arg(endDate)))
        {
            query.first();
            endId = query.value(0).toInt();
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::getData:" << query.lastError();
            qDebug() << query.lastQuery();
            _database.close();
            return data;
        }

        if (query.exec(QString("SELECT * from StaticData WHERE RunId BETWEEN %1 AND %2").arg(startId).arg(endId)))
        {
            query.first();
            do { data.push_back(convertToBrewData(query)); }
            while (query.next());
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::getData:" << query.lastError();
            qDebug() << query.lastQuery();
        }

    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::getData: unable to open database";
    }

    _database.close();

    return data;
}

BrewData DatabaseManager::getData(QString date)
{
    BrewData record;

    if (_database.open())
    {
        QSqlQuery query;

        if (query.exec(QString("SELECT RunId from StaticData WHERE BrewDate LIKE '\%\%1\%'").arg(date)))
        {
            query.first();
            record = convertToBrewData(query);
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::getData:" << query.lastError();
            qDebug() << query.lastQuery();
        }
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::getData: unable to open database";
    }

    _database.close();

    return record;
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

        if (!updateQuery.exec(QString("UPDATE TemperatureData SET Length = %1 WHERE RunId = %2").arg((int)data.temperature.size()).arg(data.run_id)))
            qDebug() << "ERROR:DatabaseManager::updateTemperature:" << updateQuery.lastError();

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

        if (!updateQuery.exec(QString("UPDATE AcidityData SET Length = %1 WHERE RunId = %2").arg((int)data.pH.size()).arg(data.run_id)))
            qDebug() << "ERROR:DatabaseManager::updateAcidity:" << updateQuery.lastError();

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

void DatabaseManager::getPhData(BrewData &data)
{
    if (_database.isOpen())
    {
        QSqlQuery query;

        if (query.exec(QString("SELECT * from AcidityData WHERE RunId = %1").arg(data.run_id)))
        {
            query.first();
            for (int ii = 0; ii < query.value(2).toInt(); ii++)
                data.pH.push_back(query.value(ii + 3).toReal());
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::getPhData:" << query.lastError();
        }
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::getPhData: unable to open database";
    }
}

void DatabaseManager::getTemperatureData(BrewData &data)
{
    if (_database.isOpen())
    {
        QSqlQuery query;

        if (query.exec(QString("SELECT * from TemperatureData WHERE RunId = %1").arg(data.run_id)))
        {
            query.first();
            for (int ii = 0; ii < query.value(2).toInt(); ii++)
                data.temperature.push_back(query.value(ii + 3).toReal());
        }
        else
        {
            qDebug() << "ERROR:DatabaseManager::getPhData:" << query.lastError();
        }
    }
    else
    {
        qDebug() << "ERROR:DatabaseManager::getPhData: unable to open database";
    }
}

BrewData DatabaseManager::convertToBrewData(const QSqlQuery &query)
{
    BrewData record;

    record.run_id = query.value(0).toInt();
    record.run = query.value(1).toString();
    record.region = query.value(2).toString();
    record.roast = query.value(3).toInt();
    record.age = query.value(4).toInt();
    record.grind = query.value(5).toInt();
    record.water = query.value(6).toReal();
    record.dosage = query.value(7).toReal();
    record.brew_time = query.value(8).toString();

    getPhData(record);
    getTemperatureData(record);

    return record;
}

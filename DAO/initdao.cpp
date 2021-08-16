#include "initdao.h"

InitDao::InitDao()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString("%1/%2").arg(QString::fromStdString(nameDirectory), QString::fromStdString(nameDatabaseFile)));

    QDir dir(QString("%1/%2").arg(QString::fromStdString(nameDirectory), QString::fromStdString(nameDatabaseFile)));

    if(!dir.exists()){
        QDir().mkdir(QString::fromStdString(nameDirectory));
        std::fstream fs;
        fs.open(QString("%1/%2").arg(QString::fromStdString(nameDirectory), QString::fromStdString(nameDatabaseFile)).toStdString()
                , std::ios::out);
        fs.close();
    }

    if(db.open()){
        qDebug() << "Fichier ouvert";
    }
    else{
        qDebug() << db.lastError();
    }

}

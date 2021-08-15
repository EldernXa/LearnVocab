#include "initdao.h"

using std::filesystem::exists;

InitDao::InitDao()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data/LearnVocab.db");

    if(!exists("data/LearnVocab.db")){
        const char* path = "data";
        std::filesystem::path dir(path);
        std::filesystem::create_directory(dir);
        std::fstream fs;
        fs.open("data/LearnVocab.db", std::ios::out);
        fs.close();
    }

    if(db.open()){
        qDebug() << "Fichier ouvert";
    }
    else{
        qDebug() << db.lastError();
    }

}

#ifndef INITDAO_H
#define INITDAO_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

#include <QDir>
#include <fstream>
#include <ios>

using namespace std;

class InitDao
{
public:
    InitDao();

private:
    const string nameDirectory = "data";
    const string nameDatabaseFile = "LearnVocab.db";
};

#endif // INITDAO_H

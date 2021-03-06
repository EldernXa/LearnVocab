#ifndef READERVOCAB_H
#define READERVOCAB_H

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>


#include <QVector>
#include <QString>
#include "CstFile/cststatic.h"

using namespace std;

class ReaderVocab
{
public:
    ReaderVocab(string);
    vector<string> getAllLineOfTheVocab();
    vector<string> getLineSplited(int);
    vector<string> getWordSplitedFromLineSplited(int, int);
    bool isLineVocabKnown(int);
    int getNumberOfColumns();
    vector<string> getColumnName();
    QVector<QVector<QVector<string>*>*> getListWord();
    QVector<QVector<QVector<string>*>*> getListWordNotKnow();
    QVector<QVector<QVector<string>*>*> getListWordKnow();

private:
    vector<string> split(const string&, char delimiter);
    void fillList(QVector<QVector<QVector<string>*>*>, vector<string>);

    string nameVocab;
    int numberOfColumn;
    fstream fileVocab;
    vector<string> nameColumns;
    vector<string> lineOfTheFile;
    QVector<QVector<QVector<string>*>*> listWord;
    QVector<QVector<QVector<string>*>*> listWordNotKnow;
    QVector<QVector<QVector<string>*>*> listWordKnow;
};

#endif // READERVOCAB_H

#ifndef READERVOCAB_H
#define READERVOCAB_H

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>


#include <QVector>
#include <QString>

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

private:
    vector<string> split(const string&, char delimiter);

    string nameVocab;
    int numberOfColumn;
    fstream fileVocab;
    vector<string> nameColumns;
    vector<string> lineOfTheFile;
    QVector<QVector<QVector<string>*>*> listWord;
};

#endif // READERVOCAB_H

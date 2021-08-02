#ifndef WRITERVOCAB_H
#define WRITERVOCAB_H

#include <iostream>
#include <fstream>
#include <vector>

#include <QLineEdit>
#include <QVector>

#include "readervocab.h"

using namespace std;

class WriterVocab
{
public:
    WriterVocab(string, int, vector<string>);
    WriterVocab(string);
    WriterVocab(string, vector<int>);
    void addLine(vector<vector<QLineEdit*>*>);
    void addLine(QVector<QVector<string>*>*);
    void close();

private:
    void writeNumberColumns(int);
    void writeListNameColumn(vector<string>);

    fstream fileVocabToWrite;
};

#endif // WRITERVOCAB_H

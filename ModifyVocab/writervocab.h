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
    WriterVocab(string, int, vector<string>, vector<vector<vector<string>>>, vector<bool>);
    void addLine(vector<vector<QLineEdit*>*>);
    void addLine(QVector<QVector<string>*>*);
    void addLine(vector<vector<string>>, bool = false);
    void close();

private:
    void writeNumberColumns(int);
    void writeListNameColumn(vector<string>);

    fstream fileVocabToWrite;
};

#endif // WRITERVOCAB_H

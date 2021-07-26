#ifndef WRITERVOCAB_H
#define WRITERVOCAB_H

#include <iostream>
#include <fstream>
#include <vector>

#include <QLineEdit>

using namespace std;

class WriterVocab
{
public:
    WriterVocab(string, int, vector<string>);
    WriterVocab(string);
    void addLine(vector<vector<QLineEdit*>*>);
    void close();

private:
    void writeNumberColumns(int);
    void writeListNameColumn(vector<string>);

    fstream fileVocabToWrite;
};

#endif // WRITERVOCAB_H

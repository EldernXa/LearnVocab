#ifndef READERVOCAB_H
#define READERVOCAB_H

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

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

private:
    vector<string> split(const string&, char delimiter);

    string nameVocab;
    int numberOfColumn;
    fstream fileVocab;
    vector<string> nameColumns;
    vector<string> lineOfTheFile;
};

#endif // READERVOCAB_H

#ifndef CSTSTATIC_H
#define CSTSTATIC_H

#include <string>

using namespace std;

class CstStatic
{
public:
    CstStatic();
    static string getPathToVocabFile();
    static string getFormatVocabFile();
    static const unsigned int LIMIT_NUMBER_WORD = 5;

private:
    static const string pathVocabFile;
    static const string formatVocabFile;
};

#endif // CSTSTATIC_H

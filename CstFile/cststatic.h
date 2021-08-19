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

private:
    static const string pathVocabFile;
    static const string formatVocabFile;
};

#endif // CSTSTATIC_H

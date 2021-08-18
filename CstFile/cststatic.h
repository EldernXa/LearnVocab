#ifndef CSTSTATIC_H
#define CSTSTATIC_H

#include <string>

using namespace std;

class CstStatic
{
public:
    CstStatic();
    static string getPathToVocabFile();

private:
    static const string pathVocabFile;
};

#endif // CSTSTATIC_H

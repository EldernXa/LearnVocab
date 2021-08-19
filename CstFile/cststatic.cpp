#include "cststatic.h"

const string CstStatic::pathVocabFile = "data/";
const string CstStatic::formatVocabFile = ".vocab";

CstStatic::CstStatic()
{}


string CstStatic::getPathToVocabFile(){
    return pathVocabFile;
}

string CstStatic::getFormatVocabFile(){
    return formatVocabFile;
}

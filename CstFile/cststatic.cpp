#include "cststatic.h"

const string CstStatic::pathVocabFile = "data/";

CstStatic::CstStatic()
{}


string CstStatic::getPathToVocabFile(){
    return pathVocabFile;
}

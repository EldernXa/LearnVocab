#include "readervocab.h"

ReaderVocab::ReaderVocab(string nameVocab)
{
    this->nameVocab = nameVocab;
    fileVocab.open(nameVocab+".vocab", ios::in);
    string value;
    getline(fileVocab, value);
    numberOfColumn = stoi(value);
    getline(fileVocab, value);
    nameColumns = split(value, ';');
    while(getline(fileVocab, value)){
        lineOfTheFile.push_back(value);
    }
}

vector<string> ReaderVocab::getAllLineOfTheVocab(){
    return lineOfTheFile;
}

vector<string> ReaderVocab::getLineSplited(int numLine){
    if(split(lineOfTheFile.at(numLine), ':').size()>1){
        return split(split(lineOfTheFile.at(numLine), ':').at(0), ';');
    }
    return split(lineOfTheFile.at(numLine), ';');
}

vector<string> ReaderVocab::getWordSplitedFromLineSplited(int numLine, int numWord){
    return split(getLineSplited(numLine).at(numWord), ',');
}

bool ReaderVocab::isLineVocabKnown(int numLine){
    if(split(lineOfTheFile.at(numLine), ':').size()>1){
        return true;
    }
    return false;
}

int ReaderVocab::getNumberOfColumns(){
    return numberOfColumn;
}

vector<string> ReaderVocab::getColumnName(){
    return nameColumns;
}

vector<string> ReaderVocab::split(const std::string& s, char delimiter){
    vector<string> tokens;
    string token;
    istringstream tokenstream(s);
    while(getline(tokenstream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}

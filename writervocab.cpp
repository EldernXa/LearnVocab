#include "writervocab.h"

WriterVocab::WriterVocab(string nameVocab, int numberOfColumns, vector<string> listNameColumn)
{
    fileVocabToWrite.open(nameVocab+".vocab", ios::out);
    writeNumberColumns(numberOfColumns);
    writeListNameColumn(listNameColumn);
}

WriterVocab::WriterVocab(string nameVocab){
    fileVocabToWrite.open(nameVocab+".vocab", ios::app);
}

void WriterVocab::writeNumberColumns(int numberOfColumns){
    fileVocabToWrite << numberOfColumns << endl;
}

void WriterVocab::writeListNameColumn(vector<string> listNameColumn){
    for(unsigned int i = 0; i<listNameColumn.size(); i++){
        fileVocabToWrite << listNameColumn.at(i);
        if(i<listNameColumn.size()-1){
            fileVocabToWrite << ";";
        }
    }
    fileVocabToWrite << endl;
}

void WriterVocab::addLine(vector<vector<QLineEdit*>*> listLineEditForWord){
    for(unsigned int indexForVect=0 ; indexForVect<listLineEditForWord.size(); indexForVect++){
        for(unsigned int indexForLineEdit = 0; indexForLineEdit<listLineEditForWord.at(indexForVect)->size(); indexForLineEdit++){
            fileVocabToWrite << listLineEditForWord.at(indexForVect)->at(indexForLineEdit)->text().toStdString();
            if(indexForLineEdit < listLineEditForWord.at(indexForVect)->size()-1){
                fileVocabToWrite<<",";
            }
        }
        if(indexForVect<listLineEditForWord.size()-1){
            fileVocabToWrite<<";";
        }else{
            fileVocabToWrite << endl;
        }
    }
}

void WriterVocab::close(){
    fileVocabToWrite.close();
}

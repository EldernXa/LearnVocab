#include "writervocab.h"

// TODO use the cst for the format for the different constructor.

WriterVocab::WriterVocab(string nameVocab, int numberOfColumns, vector<string> listNameColumn)
{
    QDir dir(QString::fromStdString(CstStatic::getPathToVocabFile()));
    if(!dir.exists()){
        QDir().mkdir(QString::fromStdString(CstStatic::getPathToVocabFile()));
    }
    fileVocabToWrite.open(CstStatic::getPathToVocabFile()+nameVocab+".vocab", ios::out);
    writeNumberColumns(numberOfColumns);
    writeListNameColumn(listNameColumn);
}

WriterVocab::WriterVocab(string nameVocab){
    fileVocabToWrite.open(CstStatic::getPathToVocabFile()+nameVocab+".vocab", ios::app);
}

WriterVocab::WriterVocab(string nameVocab, vector<int> listIndToRemove){
    ReaderVocab *readerVocab = new ReaderVocab(nameVocab);
    fileVocabToWrite.open(CstStatic::getPathToVocabFile()+nameVocab+".vocab", ios::out);
    writeNumberColumns(readerVocab->getNumberOfColumns());
    writeListNameColumn(readerVocab->getColumnName());
    QVector<QVector<QVector<string>*>*> listVoc = readerVocab->getListWord();
    for(int i = 0; i<listVoc.size(); i++){
        if(!count(listIndToRemove.begin(), listIndToRemove.end(), i)){
            addLine(listVoc.at(i));
        }
    }
}

WriterVocab::WriterVocab(string nameVocab, int numberOfColumn, vector<string> listColumn, vector<vector<vector<string>>> listWord, vector<bool> listWordIsKnow){
    fileVocabToWrite.open(CstStatic::getPathToVocabFile()+nameVocab+".vocab", ios::out);
    writeNumberColumns(numberOfColumn);
    writeListNameColumn(listColumn);
    //QVector<QVector<QVector<string>*>*> listVoc = readerVocab->getListWord();
    for(unsigned int i = 0; i<listWord.size(); i++){
//        if(!count(listIndToRemove.begin(), listIndToRemove.end(), i)){
//            addLine(listVoc.at(i));
//        }
        addLine(listWord.at(i), listWordIsKnow.at(i));
    }
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


void WriterVocab::addLine(QVector<QVector<string>*> * listLineEditForWord){
    for(int indexForVect=0 ; indexForVect<listLineEditForWord->size(); indexForVect++){
        for(int indexForLineEdit = 0; indexForLineEdit<listLineEditForWord->at(indexForVect)->size(); indexForLineEdit++){
            fileVocabToWrite << listLineEditForWord->at(indexForVect)->at(indexForLineEdit);
            if(indexForLineEdit < listLineEditForWord->at(indexForVect)->size()-1){
                fileVocabToWrite<<",";
            }
        }
        if(indexForVect<listLineEditForWord->size()-1){
            fileVocabToWrite<<";";
        }else{
            fileVocabToWrite << endl;
        }
    }
}

void WriterVocab::addLine(vector<vector<string>> listLineEditForWord, bool wordIsKnown){
    for(unsigned int indexForVect=0 ; indexForVect<listLineEditForWord.size(); indexForVect++){
        for(unsigned int indexForLineEdit = 0; indexForLineEdit<listLineEditForWord.at(indexForVect).size(); indexForLineEdit++){
            fileVocabToWrite << listLineEditForWord.at(indexForVect).at(indexForLineEdit);
            if(indexForLineEdit < listLineEditForWord.at(indexForVect).size()-1){
                fileVocabToWrite<<",";
            }
        }
        if(indexForVect<listLineEditForWord.size()-1){
            fileVocabToWrite<<";";
        }else{
            if(wordIsKnown){
                fileVocabToWrite << ":ok";
            }
            fileVocabToWrite << endl;
        }
    }
}

void WriterVocab::close(){
    fileVocabToWrite.close();
}

#include "quizvocab.h"
#include "ui_quizvocab.h"

using namespace std;

QuizVocab::QuizVocab(string nameVocabToQuiz, QuizType quizType, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuizVocab)
{
    if(quizType == randomNWord){
        ui->setupUi(this);
        nameVocab = nameVocabToQuiz;
        saveVocabWord();
        enableEvent();
    }
}

void QuizVocab::enableEvent(){
    connect(ui->pushButtonToValidNumberOfWord, SIGNAL(clicked()), this, SLOT(saveNumberOfWord()));
}

void QuizVocab::saveVocabWord(){
    fstream fileVocabToRead;
    fileVocabToRead.open(nameVocab+".vocab", ios::in);
    string valueTempForRead;
    getline(fileVocabToRead, valueTempForRead);
    numberOfColumn = stoi(valueTempForRead);
    getline(fileVocabToRead, valueTempForRead);
    for(auto& str : QString::fromStdString(valueTempForRead).split(';')){
        nameColumn.push_back(str.toStdString());
    }

    while(getline(fileVocabToRead, valueTempForRead)){
        listWord.append(new QVector<QVector<string>*>());
        for(auto& qStr : QString::fromStdString(valueTempForRead).split(";")){
            QStringList listStr = qStr.split(",");
            listWord.at(listWord.size()-1)->append(new QVector<string>());
            for(auto &s:listStr){
                listWord.at(listWord.size()-1)->at(listWord.at(listWord.size()-1)->size()-1)->push_back(s.toStdString());
            }
        }
    }
    fileVocabToRead.close();
}

void QuizVocab::saveNumberOfWord(){

}

QuizVocab::~QuizVocab()
{
    delete ui;
}

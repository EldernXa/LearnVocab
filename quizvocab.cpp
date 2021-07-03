#include "quizvocab.h"
#include "ui_quizvocab.h"

using namespace std;

QuizVocab::QuizVocab(string nameVocabToQuiz, QuizType quizType, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuizVocab)
{
    ui->setupUi(this);
    nameVocab = nameVocabToQuiz;
    saveVocabWord();
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
}

QuizVocab::~QuizVocab()
{
    delete ui;
}

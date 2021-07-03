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
        ui->labelMaxWordAvailable->setText(tr("(Le nombre maximale permis est ") + QString::number(listWord.size()) + ")");
        ui->errorInputNbOfWordLbl->setStyleSheet("QLabel {color:red;}");
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
    ui->errorInputNbOfWordLbl->setText("");
    if(ui->lineEditNumberOfWord->text().compare("")==0){
        ui->errorInputNbOfWordLbl->setText(tr("Vous devez rentrer une valeur."));
    }else{
        if(!regex_match(ui->lineEditNumberOfWord->text().toStdString(), regex{"[+-]?[0-9]+"})){
            ui->errorInputNbOfWordLbl->setText(tr("Vous devez rentrée une valeur."));
        }else if(stoi(ui->lineEditNumberOfWord->text().toStdString())<1 ||
                 stoi(ui->lineEditNumberOfWord->text().toStdString())>listWord.size()){
            ui->errorInputNbOfWordLbl->setText(tr("La valeur minimal permis est 1 et\nla valeur maximale permise est ") + QString::number(listWord.size()));
        }else{
            numberOfWord = stoi(ui->lineEditNumberOfWord->text().toStdString());
            auto rd = random_device{};
            auto rng = default_random_engine{rd()};
            shuffle(begin(listWord), end(listWord), rng);
            cout << listWord.at(0)->at(0)->at(0) << endl;
        }
    }
}

QuizVocab::~QuizVocab()
{
    delete ui;
}

























#include "widgetquizvocab.h"
#include "ui_widgetquizvocab.h"

WidgetQuizVocab::WidgetQuizVocab(string nameVocabToQuiz, QuizType quizType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetQuizVocab)
{
    ui->setupUi(this);
    nameVocab = nameVocabToQuiz;
    saveVocabWord();
    if(quizType == randomNWord){
        ui->widget->getLblMaxWord()->setText(tr("(Le nombre maximale permis est %1)").arg(listWord.size()));
        enableEvent();
    }
}

void WidgetQuizVocab::enableEvent(){
    connect(ui->widget->getValidButton(), SIGNAL(clicked()), this, SLOT(saveNumberOfWord()));
}

void WidgetQuizVocab::saveVocabWord(){
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
        for(auto& qStr: QString::fromStdString(valueTempForRead).split(";")){
            QStringList listStr = qStr.split(";");
            listWord.at(listWord.size()-1)->append(new QVector<string>());
            for(auto &s:listStr){
                listWord.at(listWord.size()-1)->at(listWord.at(listWord.size()-1)->size()-1)->push_back(s.toStdString());
            }
        }
    }
    fileVocabToRead.close();
}

void WidgetQuizVocab::saveNumberOfWord(){
    ui->widget->getLblError()->setText("");
    if(ui->widget->getLineEditForMaxWord()->text().compare("")==0){
        ui->widget->getLblError()->setText(tr("Vous devez rentrer une valeur."));
    }else{
        if(!regex_match(ui->widget->getLineEditForMaxWord()->text().toStdString(), regex{"[+-]?[0-9]+"})){
            ui->widget->getLblError()->setText(tr("Vous devez utilisez des chiffres uniquement."));
        }else if(stoi(ui->widget->getLineEditForMaxWord()->text().toStdString())<1 ||
                 stoi(ui->widget->getLineEditForMaxWord()->text().toStdString())>listWord.size()){
            ui->widget->getLblError()->setText(tr("La valeur minimal permis est 1 et\nla valeur maximale permise est %1.").arg(listWord.size()));
        }else{
            numberOfWord = stoi(ui->widget->getLineEditForMaxWord()->text().toStdString());
            auto rd = random_device{};
            auto rng = default_random_engine{rd()};
            shuffle(begin(listWord), end(listWord), rng);
            //cout << listWord.at(0)->at(0)->at(0) << endl;
            startingQuiz();
        }
    }
}

void WidgetQuizVocab::startingQuiz(){
    clearLayout(ui->widget->layout());
    WidgetQuizVocabLastStep* widgetQuizLastStep = new WidgetQuizVocabLastStep;
    srand(time(NULL));
    int randNum = rand()%(listWord.at(actualWord)->size()-0 + 1) + 0;
    for(unsigned int i = 0; i< nameColumn.size();i++){
        QLabel* lbl = new QLabel;
        lbl->setText(QString::fromStdString(nameColumn.at(i)));
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setFixedWidth(200);
        widgetQuizLastStep->getLayoutNameColumn()->addWidget(lbl);
    }
    QHBoxLayout* vBoxLayout = new QHBoxLayout;
    for(int i=0; i<listWord.at(actualWord)->size();i++){
        QVBoxLayout *layout = new QVBoxLayout;
        for(int j=0; j<listWord.at(actualWord)->at(i)->size();j++){
            if(i==randNum){
                QLabel *lbl = new QLabel;
                lbl->setText(QString::fromStdString(listWord.at(actualWord)->at(i)->at(j)));
                lbl->setAlignment(Qt::AlignCenter);
                lbl->setFixedWidth(200);
                layout->addWidget(lbl);
            }else{
                QLineEdit* lineEdit = new QLineEdit;
                lineEdit->setFixedWidth(200);
                layout->addWidget(lineEdit);
            }
        }
        vBoxLayout->addLayout(layout);
    }
    widgetQuizLastStep->getLayoutForQLineEdit()->addLayout(vBoxLayout);
    widgetQuizLastStep->getNumberWordMissing()->setText(QString::number(actualWord+1) + " / " + QString::number(listWord.size()));
    ui->widget->layout()->addWidget(widgetQuizLastStep);
}

void WidgetQuizVocab::clearLayout(QLayout* layout, bool deleteWidgets){
    while(QLayoutItem* item = layout->takeAt(0)){
        if(deleteWidgets){
            if(QWidget* widget = item->widget()){
                widget->deleteLater();
            }
        }
        if(QLayout* childLayout = item->layout()){
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

WidgetQuizVocab::~WidgetQuizVocab()
{
    delete ui;
}




















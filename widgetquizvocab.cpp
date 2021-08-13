#include "widgetquizvocab.h"
#include "ui_widgetquizvocab.h"

WidgetQuizVocab::WidgetQuizVocab(string nameVocabToQuiz, QuizType quizType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetQuizVocab)
{
    ui->setupUi(this);
    nameVocab = nameVocabToQuiz;
    //saveVocabWord();
    ReaderVocab *readerVocab = new ReaderVocab(nameVocab);
    if(quizType == randomNWord){
        listWord = readerVocab->getListWord();
    }else if(quizType == NFirstWordKnow){
        listWord = readerVocab->getListWordKnow();
    }else if(quizType == NFirstWordNotKnow){
        listWord = readerVocab->getListWordNotKnow();
    }

    ui->widget->getLblMaxWord()->setText(tr("(Le nombre maximale permis est %1)").arg(listWord.size()));
    enableEvent();
}

void WidgetQuizVocab::enableEvent(){
    connect(ui->widget->getValidButton(), SIGNAL(clicked()), this, SLOT(saveNumberOfWord()));
}

void WidgetQuizVocab::saveVocabWord(){
    ReaderVocab *readerVocab = new ReaderVocab(nameVocab);
    listWord = readerVocab->getListWord();
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
    widgetQuizLastStep = new WidgetQuizVocabLastStep;
    srand(time(NULL));
    randNum = rand()%(listWord.at(actualWord)->size()-1-0 + 1) + 0;
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
        if(i!=randNum){
            listLineEdit.push_back(new vector<QLineEdit*>);
        }
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
                listLineEdit.at(listLineEdit.size()-1)->push_back(lineEdit);
                layout->addWidget(lineEdit);
            }
        }
        vBoxLayout->addLayout(layout);
    }
    widgetQuizLastStep->getLayoutForQLineEdit()->addLayout(vBoxLayout);
    widgetQuizLastStep->getNumberWordMissing()->setText(QString::number(actualWord+1) + " / " + QString::number(numberOfWord));
    ui->widget->layout()->addWidget(widgetQuizLastStep);

    connect(widgetQuizLastStep->getConfirmButton(), SIGNAL(clicked()), this, SLOT(correctVocab()));
    connect(widgetQuizLastStep->getNextWordBtn(), SIGNAL(clicked()), this, SLOT(nextVocab()));
}

void WidgetQuizVocab::nextVocab(){
    actualWord++;
    if(actualWord+1==numberOfWord){
        widgetQuizLastStep->getNextWordBtn()->setText("Terminer");
        widgetQuizLastStep->getNextWordBtn()->disconnect();
        connect(widgetQuizLastStep->getNextWordBtn(), SIGNAL(clicked()), this, SLOT(finishQuiz()));
    }
    clearLayout(widgetQuizLastStep->getLayoutForQLineEdit());
    widgetQuizLastStep->getConfirmButton()->setEnabled(true);
    widgetQuizLastStep->getNextWordBtn()->setEnabled(false);
    listLineEdit.clear(); // TODO delete all widget inside instead of clear it.
    srand(time(NULL));
    randNum = rand()%(listWord.at(actualWord)->size()-1-0 + 1) + 0;
    QHBoxLayout* vBoxLayout = new QHBoxLayout;
    for(int i=0; i<listWord.at(actualWord)->size();i++){
        QVBoxLayout* layout = new QVBoxLayout;
        if(i!=randNum){
            listLineEdit.push_back(new vector<QLineEdit*>);
        }
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
                listLineEdit.at(listLineEdit.size()-1)->push_back(lineEdit);
                layout->addWidget(lineEdit);
            }
        }
        vBoxLayout->addLayout(layout);
    }
    widgetQuizLastStep->getLayoutForQLineEdit()->addLayout(vBoxLayout);
    widgetQuizLastStep->getNumberWordMissing()->setText(QString::number(actualWord+1) + " / " + QString::number(numberOfWord));
}

void WidgetQuizVocab::finishQuiz(){
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void WidgetQuizVocab::correctVocab(){
    clearLayout(widgetQuizLastStep->getLayoutForQLineEdit());
    widgetQuizLastStep->getConfirmButton()->setEnabled(false);
    widgetQuizLastStep->getNextWordBtn()->setEnabled(true);
    QHBoxLayout* vBoxLayout = new QHBoxLayout;
    bool verifRand = false;
    for(int i = 0; i<listWord.at(actualWord)->size(); i++){
        QVBoxLayout *layout = new QVBoxLayout;
        for(int j=0; j<listWord.at(actualWord)->at(i)->size();j++){
            QLabel *lbl = new QLabel;
            lbl->setText(QString::fromStdString(listWord.at(actualWord)->at(i)->at(j)));
            lbl->setAlignment(Qt::AlignCenter);
            lbl->setFixedWidth(200);

            if(randNum != i){
                int num;
                if(!verifRand){
                    num = i;
                }
                else{
                    num = i-1;
                }
                if(listLineEdit.at(num)->at(j)->text().compare(QString::fromStdString(listWord.at(actualWord)->at(i)->at(j)))==0){
                    lbl->setStyleSheet("QLabel {color:green;}");
                }else{
                    lbl->setStyleSheet("QLabel {color:red};");
                }
                num++;
            }else{
                verifRand = true;
            }

            layout->addWidget(lbl);
        }
        vBoxLayout->addLayout(layout);

    }
    widgetQuizLastStep->getLayoutForQLineEdit()->addLayout(vBoxLayout);

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
    delete widgetQuizLastStep;
    delete ui;
}




















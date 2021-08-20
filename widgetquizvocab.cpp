#include "widgetquizvocab.h"
#include "ui_widgetquizvocab.h"

WidgetQuizVocab::WidgetQuizVocab(string nameVocabToQuiz, QuizType quizType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetQuizVocab)
{
    ui->setupUi(this);
    nameVocab = nameVocabToQuiz;
    ReaderVocab *readerVocab = new ReaderVocab(nameVocab);
    numberOfColumn = readerVocab->getNumberOfColumns();
    if(quizType == randomNWord){
        listWord = readerVocab->getListWord();
    }else if(quizType == NRandomWordKnow || quizType == NFirstWordKnow){
        listWord = readerVocab->getListWordKnow();
    }else if(quizType == NRandomWordNotKnow || quizType == NFirstWordNotKnow){
        listWord = readerVocab->getListWordNotKnow();
    }

    if(quizType == NFirstWordKnow || quizType == NFirstWordNotKnow){
        firstWord = true;
    }
    GlobalFct::changeSizeFontOfLbl(ui->widget->getLblMaxWord(), this->width(), this->height());
    ui->widget->getLblMaxWord()->setText(tr("(Le nombre maximale permis est %1)").arg(listWord.size()));
    enableEvent();
}

void WidgetQuizVocab::enableEvent(){
    connect(ui->widget->getValidButton(), SIGNAL(clicked()), this, SLOT(saveNumberOfWord()));
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
            shuffle(begin(listWord), begin(listWord)+numberOfWord, rng);
            startingQuiz();
        }
    }
}

void WidgetQuizVocab::startingQuiz(){
    isFirstStep = false;
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
                GlobalFct::changeSizeFontOfLbl(lbl, this->width(), this->height());
                lbl->setMinimumWidth(this->width()/numberOfColumn);
                lbl->setText(QString::fromStdString(listWord.at(actualWord)->at(i)->at(j)));
                lbl->setAlignment(Qt::AlignCenter);
                listLbl.push_back(lbl);
                layout->addWidget(lbl);
            }else{
                QLineEdit* lineEdit = new QLineEdit;
                GlobalFct::changeSizeFontOfLineEdit(lineEdit, this->width(), this->height());
                listLineEdit.at(listLineEdit.size()-1)->push_back(lineEdit);
                layout->addWidget(lineEdit);
            }
        }
        vBoxLayout->addLayout(layout);
    }
    GlobalFct::changeSizeFontOfLbl(widgetQuizLastStep->getNumberWordMissing(), this->width(), this->height());
    GlobalFct::changeSizeFontOfPushButton(widgetQuizLastStep->getConfirmButton(), this->width(), this->height());
    GlobalFct::changeSizeFontOfPushButton(widgetQuizLastStep->getNextWordBtn(), this->width(), this->height());
    widgetQuizLastStep->getLayoutForQLineEdit()->addLayout(vBoxLayout);
    widgetQuizLastStep->getNumberWordMissing()->setText(QString::number(actualWord+1) + " / " + QString::number(numberOfWord));
    ui->widget->layout()->addWidget(widgetQuizLastStep);

    connect(widgetQuizLastStep->getConfirmButton(), SIGNAL(clicked()), this, SLOT(correctVocab()));
    connect(widgetQuizLastStep->getNextWordBtn(), SIGNAL(clicked()), this, SLOT(nextVocab()));
}

void WidgetQuizVocab::resizeEvent(QResizeEvent *resizeEvent){
    if(isFirstStep){
        GlobalFct::changeSizeFontOfLbl(ui->widget->getLblMaxWord(), this->width(), this->height());
        GlobalFct::changeSizeFontOfLbl(ui->widget->getLblTitle(), this->width(), this->height());
        GlobalFct::changeSizeFontOfLbl(ui->widget->getLblError(), this->width(), this->height());
        GlobalFct::changeSizeFontOfPushButton(ui->widget->getValidButton(), this->width(), this->height());
    }else if(widgetQuizLastStep != nullptr){
        GlobalFct::changeSizeFontOfLbl(widgetQuizLastStep->getNumberWordMissing(), this->width(), this->height());
        GlobalFct::changeSizeFontOfPushButton(widgetQuizLastStep->getConfirmButton(), this->width(), this->height());
        GlobalFct::changeSizeFontOfPushButton(widgetQuizLastStep->getNextWordBtn(), this->width(), this->height());
    }
    for(unsigned int i = 0; i<listLineEdit.size(); i++){
        for(unsigned int j=0; j<listLineEdit.at(i)->size(); j++){
            QLineEdit *lineEdit = listLineEdit.at(i)->at(j);
            GlobalFct::changeSizeFontOfLineEdit(lineEdit, this->width(), this->height());
        }
    }

    for(QLabel *lbl : listLbl){
        GlobalFct::changeSizeFontOfLbl(lbl, this->width(), this->height());
        lbl->setMinimumWidth(this->width()/numberOfColumn);
    }
    QWidget::resizeEvent(resizeEvent);
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
    listLbl.clear(); // TODO delete all widget here to instead of just clear it.
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
                lbl->setMinimumWidth(this->width()/numberOfColumn);
                GlobalFct::changeSizeFontOfLbl(lbl, this->width(), this->height());
                lbl->setText(QString::fromStdString(listWord.at(actualWord)->at(i)->at(j)));
                lbl->setAlignment(Qt::AlignCenter);
                layout->addWidget(lbl);
                listLbl.push_back(lbl);
            }else{
                QLineEdit* lineEdit = new QLineEdit;
                GlobalFct::changeSizeFontOfLineEdit(lineEdit, this->width(), this->height());
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
            GlobalFct::changeSizeFontOfLbl(lbl, this->width(), this->height());

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
    if(widgetQuizLastStep != nullptr){
        delete widgetQuizLastStep;
    }
    delete ui;
}




















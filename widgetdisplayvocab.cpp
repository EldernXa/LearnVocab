#include "widgetdisplayvocab.h"
#include "ui_widgetdisplayvocab.h"

WidgetDisplayVocab::WidgetDisplayVocab(std::string nameVocab, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetDisplayVocab)
{
    ui->setupUi(this);
    nameVocabToDisplay = nameVocab;
//    QWidget *scrollAreaContent = new QWidget;
//    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    ui->scrollArea->setWidgetResizable(true);
//    ui->scrollArea->setWidget(scrollAreaContent);

    fileToDisplayVocab.open(nameVocab+".vocab", ios::in);
    string value;
    getline(fileToDisplayVocab, value);
    numberOfColumn = stoi(value);
    getline(fileToDisplayVocab, value);
    nameColumns = split(value, ';');

    this->resize(numberOfColumn*WIDTH_LABEL + WIDTH_LABEL, 400);
    ui->widget->setLayout(new QVBoxLayout);
    QWidget *widgetForNameColumns = new QWidget;
    ui->widget->layout()->addWidget(widgetForNameColumns);
    QHBoxLayout *layoutForNameColumns = new QHBoxLayout(widgetForNameColumns);
    for(auto &nameColumn : nameColumns){
        QLabel *lblNameColumn = new QLabel;
        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setAlignment(Qt::AlignCenter);
        //lblNameColumn->setFixedHeight(HEIGHT_LABEL);
        //lblNameColumn->setFixedWidth(WIDTH_LABEL);
        layoutForNameColumns->addWidget(lblNameColumn);
    }
    lastHeight += HEIGHT_LABEL+1;
    QFrame *frameVLine = new QFrame;
    ui->widget->layout()->addWidget(frameVLine);
    //frameVLine->setFixedWidth(numberOfColumn*WIDTH_LABEL);
    frameVLine->setFrameShape(QFrame::HLine);
    frameVLine->move(0, lastHeight);
    while(getline(fileToDisplayVocab, value)){
        bool verifIsKnown = split(value, ':').size()>1;
        vector<string> valueToDisplay = split(split(value, ':').at(0), ';');
        QWidget *widgetForNameWord = new QWidget;
        ui->widget->layout()->addWidget(widgetForNameWord);
        QHBoxLayout *layoutForNameWord = new QHBoxLayout(widgetForNameWord);
        widgetForNameWord->move(0, lastHeight);
        unsigned int multiply_value = 1;
        for(auto &nameWord : valueToDisplay){
            vector<string> differentValueForAWord = split(nameWord, ',');
            if(differentValueForAWord.size()>1){
                QWidget *widgetForAWord = new QWidget;
                QVBoxLayout *layoutForAWord = new QVBoxLayout(widgetForAWord);
                layoutForAWord->setSpacing(0);
                if(differentValueForAWord.size()>multiply_value){
                    multiply_value = differentValueForAWord.size();
                }
                for(auto &word : differentValueForAWord){
                    QLabel *lblNameWord = new QLabel;
                    lblNameWord->setAlignment(Qt::AlignCenter);
                    lblNameWord->setText(QString::fromStdString(word));
                    //lblNameWord->setFixedHeight(HEIGHT_LABEL);
                    //lblNameWord->setFixedWidth(WIDTH_LABEL);
                    if(verifIsKnown){
                        lblNameWord->setStyleSheet("QLabel {color:green;}");
                    }else{
                        lblNameWord->setStyleSheet("QLabel {color:red;}");
                    }
                    layoutForAWord->addWidget(lblNameWord);
                }
                layoutForNameWord->addWidget(widgetForAWord);
            }else{
                QLabel *lblNameWord = new QLabel;
                lblNameWord->setAlignment(Qt::AlignCenter);
                lblNameWord->setText(QString::fromStdString(nameWord));
                //lblNameWord->setFixedHeight(HEIGHT_LABEL);
                //lblNameWord->setFixedWidth(WIDTH_LABEL);
                if(verifIsKnown){
                    lblNameWord->setStyleSheet("QLabel {color:green;}");
                }else{
                    lblNameWord->setStyleSheet("QLabel {color:red;}");
                }
                layoutForNameWord->addWidget(lblNameWord);
            }
        }
        lastHeight+=(HEIGHT_LABEL*multiply_value);
        QFrame *frameLine = new QFrame;
        ui->widget->layout()->addWidget(frameLine);
        //frameLine->setFixedWidth(numberOfColumn*WIDTH_LABEL);
        frameLine->setFrameShape(QFrame::HLine);
        frameLine->move(0, lastHeight);
    }
    fileToDisplayVocab.close();

}

std::vector<std::string> WidgetDisplayVocab::split(const std::string& s, char delimiter){
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while(std::getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}

WidgetDisplayVocab::~WidgetDisplayVocab()
{
    delete ui;
}

void WidgetDisplayVocab::on_buttonBack_clicked()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}


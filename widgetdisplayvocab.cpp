#include "widgetdisplayvocab.h"
#include "ui_widgetdisplayvocab.h"

WidgetDisplayVocab::WidgetDisplayVocab(std::string nameVocab, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetDisplayVocab)
{
    ui->setupUi(this);
    nameVocabToDisplay = nameVocab;
    readerVocab = new ReaderVocab(nameVocab);
    ui->widget->setLayout(new QVBoxLayout);
    QWidget *widgetForNameColumns = new QWidget;
    ui->widget->layout()->addWidget(widgetForNameColumns);
    QHBoxLayout *layoutForNameColumns = new QHBoxLayout(widgetForNameColumns);
    for(auto &nameColumn : readerVocab->getColumnName()){
        QLabel *lblNameColumn = new QLabel;
        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setAlignment(Qt::AlignCenter);
        layoutForNameColumns->addWidget(lblNameColumn);
    }
    QFrame *frameVLine = new QFrame;
    ui->widget->layout()->addWidget(frameVLine);
    frameVLine->setFrameShape(QFrame::HLine);

    for (unsigned int i=0; i< readerVocab->getAllLineOfTheVocab().size(); i++){
        bool verifIsKnown = readerVocab->isLineVocabKnown(i);
        vector<string> valueToDisplay = readerVocab->getLineSplited(i);
        QWidget *widgetForNameWord = new QWidget;
        ui->widget->layout()->addWidget(widgetForNameWord);
        QHBoxLayout *layoutForNameWord = new QHBoxLayout(widgetForNameWord);
        unsigned int multiply_value = 1;
        for(unsigned int j = 0; j<valueToDisplay.size(); j++){
            vector<string> differentValueForAWord = readerVocab->getWordSplitedFromLineSplited(i, j);
            if(differentValueForAWord.size()>1){
                QWidget *widgetForAWord = new QWidget;
                QVBoxLayout *layoutForAWord = new QVBoxLayout(widgetForAWord);
                layoutForAWord->setSpacing(0);
                if(differentValueForAWord.size()>multiply_value){
                    multiply_value = differentValueForAWord.size();
                }

                for(auto& word : differentValueForAWord){
                    QLabel *lblNameWord = new QLabel;
                    lblNameWord->setAlignment(Qt::AlignCenter);
                    lblNameWord->setText(QString::fromStdString(word));
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
                lblNameWord->setText(QString::fromStdString(valueToDisplay.at(j)));
                if(verifIsKnown){
                    lblNameWord->setStyleSheet("QLabel {color:green;}");
                }else{
                    lblNameWord->setStyleSheet("QLabel {color:red;}");
                }
                layoutForNameWord->addWidget(lblNameWord);
            }
        }
        QFrame *frameLine = new QFrame;
        ui->widget->layout()->addWidget(frameLine);
        frameLine->setFrameShape(QFrame::HLine);
        QSpacerItem *itemSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
        ui->widget->layout()->addItem(itemSpacer);
    }
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


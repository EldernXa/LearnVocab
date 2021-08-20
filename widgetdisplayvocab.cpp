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

        GlobalFct::changeSizeFontOfLbl(lblNameColumn, this->width(), this->height());

        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setAlignment(Qt::AlignCenter);
        listLblNameColumn.push_back(lblNameColumn);
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
        for(unsigned int j = 0; j<valueToDisplay.size(); j++){
            vector<string> differentValueForAWord = readerVocab->getWordSplitedFromLineSplited(i, j);
            //if(differentValueForAWord.size()>1){
                QWidget *widgetForAWord = new QWidget;
                QVBoxLayout *layoutForAWord = new QVBoxLayout(widgetForAWord);
                layoutForAWord->setSpacing(0);

                for(auto& word : differentValueForAWord){
                    QLabel *lblNameWord = new QLabel;
                    GlobalFct::changeSizeFontOfLbl(lblNameWord, this->width(), this->height());
                    listLblWord.push_back(lblNameWord);
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
//            }else{
//                QLabel *lblNameWord = new QLabel;
//                lblNameWord->setAlignment(Qt::AlignCenter);
//                lblNameWord->setText(QString::fromStdString(valueToDisplay.at(j)));
//                if(verifIsKnown){
//                    lblNameWord->setStyleSheet("QLabel {color:green;}");
//                }else{
//                    lblNameWord->setStyleSheet("QLabel {color:red;}");
//                }
//                layoutForNameWord->addWidget(lblNameWord);
//            }
        }
        QFrame *frameLine = new QFrame;
        ui->widget->layout()->addWidget(frameLine);
        frameLine->setFrameShape(QFrame::HLine);
        QSpacerItem *itemSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
        ui->widget->layout()->addItem(itemSpacer);
    }
}

void WidgetDisplayVocab::resizeEvent(QResizeEvent *event){
    for(QLabel *lbl : listLblNameColumn){
        GlobalFct::changeSizeFontOfLbl(lbl, this->width(), this->height());
    }
    for(QLabel *lbl : listLblWord){
        GlobalFct::changeSizeFontOfLbl(lbl, this->width(), this->height());
    }
    QWidget::resizeEvent(event);
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


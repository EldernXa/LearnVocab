#include "widgetquizvocabinitstep.h"
#include "ui_widgetquizvocabinitstep.h"

WidgetQuizVocabInitStep::WidgetQuizVocabInitStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetQuizVocabInitStep)
{
    ui->setupUi(this);
}

QLabel* WidgetQuizVocabInitStep::getLblTitle(){
    return ui->labelTitle;
}

QLabel* WidgetQuizVocabInitStep::getLblMaxWord(){
    return ui->nbWordMax;
}

QLabel* WidgetQuizVocabInitStep::getLblError(){
    return ui->labelError;
}

QLineEdit* WidgetQuizVocabInitStep::getLineEditForMaxWord(){
    return ui->lineEditForNbWord;
}

QPushButton* WidgetQuizVocabInitStep::getValidButton(){
    return ui->validBtn;
}


WidgetQuizVocabInitStep::~WidgetQuizVocabInitStep()
{
    delete ui;
}

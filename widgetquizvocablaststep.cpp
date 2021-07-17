#include "widgetquizvocablaststep.h"
#include "ui_widgetquizvocablaststep.h"

WidgetQuizVocabLastStep::WidgetQuizVocabLastStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetQuizVocabLastStep)
{
    ui->setupUi(this);
}

QHBoxLayout* WidgetQuizVocabLastStep::getLayoutNameColumn(){
    return ui->layoutNameColumn;
}

QHBoxLayout* WidgetQuizVocabLastStep::getLayoutForQLineEdit(){
    return ui->layoutQLineEdit;
}

QPushButton* WidgetQuizVocabLastStep::getConfirmButton(){
    return ui->validButton;
}

QLabel* WidgetQuizVocabLastStep::getNumberWordMissing(){
    return ui->lblWordMissing;
}

QPushButton* WidgetQuizVocabLastStep::getNextWordBtn(){
    return ui->nextWordBtn;
}



WidgetQuizVocabLastStep::~WidgetQuizVocabLastStep()
{
    delete ui;
}

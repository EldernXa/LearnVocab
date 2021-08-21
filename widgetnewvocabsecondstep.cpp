#include "widgetnewvocabsecondstep.h"
#include "ui_widgetnewvocabsecondstep.h"

WidgetNewVocabSecondStep::WidgetNewVocabSecondStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewVocabSecondStep)
{
    ui->setupUi(this);
}

QLineEdit* WidgetNewVocabSecondStep::getFirstLineEdit(){
    return ui->lineEdit;
}

QLineEdit* WidgetNewVocabSecondStep::getSecondLineEdit(){
    return ui->lineEdit_2;
}

QPushButton* WidgetNewVocabSecondStep::getValidButton(){
    return ui->pushButton;
}

void WidgetNewVocabSecondStep::addWidgetToLayout(QWidget *widgetToAdd){
    ui->horizontalLayoutForNameColumn->addWidget(widgetToAdd);
}

QLabel* WidgetNewVocabSecondStep::getErrorLabel(){
    return ui->errorLabelForNameColumn;
}

QLabel* WidgetNewVocabSecondStep::getLblNameColumn(){
    return ui->labelNameColumn;
}

WidgetNewVocabSecondStep::~WidgetNewVocabSecondStep()
{
    delete ui;
}

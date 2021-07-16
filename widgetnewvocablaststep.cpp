#include "widgetnewvocablaststep.h"
#include "ui_widgetnewvocablaststep.h"

WidgetNewVocabLastStep::WidgetNewVocabLastStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewVocabLastStep)
{
    ui->setupUi(this);
}

QHBoxLayout* WidgetNewVocabLastStep::getLayoutForAddingBtn(){
    return ui->layoutAddingBtn;
}

QHBoxLayout* WidgetNewVocabLastStep::getLayoutForNameColumn(){
    return ui->layoutLblName;
}

QHBoxLayout* WidgetNewVocabLastStep::getLayoutForQLineEdit(){
    return ui->layoutForQLineEdit;
}

QHBoxLayout* WidgetNewVocabLastStep::getLayoutForRemovingBtn(){
    return ui->layoutRemovingBtn;
}

QPushButton* WidgetNewVocabLastStep::getBtnAddWord(){
    return ui->btnAddWord;
}

QPushButton* WidgetNewVocabLastStep::getConfirmBtn(){
    return ui->validBtn;
}

QLabel* WidgetNewVocabLastStep::getLblLastWord(){
    return ui->lblLastWord;
}

QLabel* WidgetNewVocabLastStep::getLblError(){
    return ui->lblError;
}




WidgetNewVocabLastStep::~WidgetNewVocabLastStep()
{
    delete ui;
}

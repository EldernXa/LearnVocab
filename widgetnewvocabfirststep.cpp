#include "widgetnewvocabfirststep.h"
#include "ui_widgetnewvocabfirststep.h"

WidgetNewVocabFirstStep::WidgetNewVocabFirstStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewVocabFirstStep)
{
    ui->setupUi(this);
}

QPushButton* WidgetNewVocabFirstStep::getButton(){
    return ui->firstButtonForCreateVocab;
}

QLabel* WidgetNewVocabFirstStep::getLabelError(){
    return ui->labelError;
}

QLineEdit* WidgetNewVocabFirstStep::getLineEditForName(){
    return ui->lineEditForName;
}

QLineEdit* WidgetNewVocabFirstStep::getLineEditNumberOfColumn(){
    return ui->lineEditNumberColumn;
}

WidgetNewVocabFirstStep::~WidgetNewVocabFirstStep()
{
    delete ui;
}

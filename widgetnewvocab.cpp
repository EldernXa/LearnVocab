#include "widgetnewvocab.h"
#include "ui_widgetnewvocab.h"

// TODO verify if the vocab doesn't actually exist.

WidgetNewVocab::WidgetNewVocab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewVocab)
{
    ui->setupUi(this);
    enableEventForFirstStep();
}

void WidgetNewVocab::enableEventForFirstStep(){
    connect(ui->widget_2->getButton(), SIGNAL(clicked()), this, SLOT(runFirstButton()));
}

void WidgetNewVocab::runFirstButton(){
    ui->widget_2->getLabelError()->setText("");
    if(ui->widget_2->getLineEditForName()->text() == ""){
        ui->widget_2->getLabelError()->setText(tr("Vous n'avez pas rentrée de nom\n pour le nouveau vocabulaire."));
    }else if(ui->widget_2->getLineEditNumberOfColumn()->text() == ""){
        ui->widget_2->getLabelError()->setText(tr("Vous n'avez pas indiquée combien de colonne\n vous voulez avoir."));
    }else{
        if(!regex_match(ui->widget_2->getLineEditNumberOfColumn()->text().toStdString(), regex{"[+-]?[0-9]+"})){
            ui->widget_2->getLabelError()->setText(tr("La valeur entrée pour le nombre\n de colonne n'est pas un entier !"));
        }else{
            if(ui->widget_2->getLineEditNumberOfColumn()->text().toInt()<=1){
                ui->widget_2->getLabelError()->setText(tr("La valeur minimum requise est de 2."));
            }else if(ui->widget_2->getLineEditNumberOfColumn()->text().toInt()>4){
                ui->widget_2->getLabelError()->setText(tr("La valeur maximum requise est de 4."));
            }
            else{
                cout << "okok" << endl;
            }
        }
    }
}

WidgetNewVocab::~WidgetNewVocab()
{
    delete ui;
}



















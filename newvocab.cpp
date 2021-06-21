#include "newvocab.h"
#include "ui_newvocab.h"

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return is_base_of<Base, T>::value;
}

NewVocab::NewVocab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewVocab)
{
    ui->setupUi(this);
    ui->widgetForCreateNewVocab->adjustSize();
    this->resize(ui->widgetForCreateNewVocab->width()+40, ui->widgetForCreateNewVocab->height()+40);
    enableEvent();
    ui->labelError->setStyleSheet("QLabel {color:red;}");
    errorLabelForNameColumn->setStyleSheet("QLabel {color:red;}");
}

void NewVocab::resizeEvent(QResizeEvent *qresizeEvent){
    this->setFixedWidth(ui->widgetForCreateNewVocab->width()+40);
    this->setFixedHeight(ui->widgetForCreateNewVocab->height()+40);
    QWidget::resizeEvent(qresizeEvent);
}

void NewVocab::enableEvent(){
    connect(ui->firstButtonForCreateVocab, SIGNAL(clicked()), this, SLOT(runFirstButton()));
}

void NewVocab::runFirstButton(){
    ui->labelError->setText("");
    if(ui->lineEditForName->text() == ""){
        ui->labelError->setText("Vous n'avez pas rentrée de nom\n pour le nouveau vocabulaire.");
    }
    else if(ui->lineEditNumberOfColumn->text() == ""){
        ui->labelError->setText("Vous n'avez pas indiquée combien de colonne\n vous voulez avoir.");
    }else{
        if(!regex_match(ui->lineEditNumberOfColumn->text().toStdString(), std::regex{"[+-]?[0-9]+"})){
            ui->labelError->setText("La valeur entrée pour le nombre\n de colonne n'est pas un entier !");
        }else{
            if(ui->lineEditNumberOfColumn->text().toInt()<=1){
                ui->labelError->setText("Valeur minimum requise est de 2.");
            }else if(ui->lineEditNumberOfColumn->text().toInt()>4){
                ui->labelError->setText("Valeur maximum permise est de 4.");
            }
            else{
                nameVocab = ui->lineEditForName->text().toStdString();
                clearLayout(ui->layoutForCreateNewVocab);
                QVBoxLayout *newQVBoxLayout = new QVBoxLayout;
                ui->centralwidget->setLayout(newQVBoxLayout);
                QLabel *newlbl = new QLabel;
                newlbl->setText("Nom des colonnes :");
                newQVBoxLayout->addWidget(newlbl);
                QHBoxLayout *hboxLayout = new QHBoxLayout;
                hboxLayout->setSpacing(2);
                newQVBoxLayout->addLayout(hboxLayout);
                numberOfColumn = ui->lineEditNumberOfColumn->text().toInt();
                this->setFixedWidth(250*numberOfColumn+40);
                ui->centralwidget->setFixedWidth(250*numberOfColumn+40+5*numberOfColumn);
                for(int i=0; i<numberOfColumn; i++){
                    QLineEdit *qlineEdit = new QLineEdit;
                    qlineEdit->setFixedWidth(250);
                    listLineEdit.push_back(qlineEdit);
                    hboxLayout->addWidget(qlineEdit);
                }
                QPushButton *termineAddingNameForColumn = new QPushButton;
                termineAddingNameForColumn->setText("Valider");
                termineAddingNameForColumn->setFixedWidth(250);
                newQVBoxLayout->addWidget(termineAddingNameForColumn);
                newQVBoxLayout->addWidget(errorLabelForNameColumn);
                connect(termineAddingNameForColumn, SIGNAL(clicked()), this, SLOT(valideNameColumn()));
            }
        }
    }
}

void NewVocab::valideNameColumn(){
    fstream file;

    file.open(nameVocab+".vocab", ios::out);
    if(verifLineEdit()){
        saveColumnName();
        file << numberOfColumn << endl;
        for(unsigned int i=0; i<listNameColumn.size();i++){
            file << listNameColumn.at(i);
            if(i<listNameColumn.size()-1){
                file<<";";
            }
        }
        file << endl;
        QWidget *newWidget = new QWidget;
        QVBoxLayout *newQVBoxLayout = new QVBoxLayout;
        newWidget->setLayout(newQVBoxLayout);
        setCentralWidget(newWidget);
        QHBoxLayout *displayColumn = new QHBoxLayout;
        QHBoxLayout *layoutForButtonAddWord = new QHBoxLayout;
        newQVBoxLayout->addLayout(displayColumn);
        newQVBoxLayout->addLayout(layoutForButtonAddWord);
        QVBoxLayout *boxAllWord = new QVBoxLayout;
        for(auto&& s : listNameColumn){
            QLabel *lblNameColumn = new QLabel;
            lblNameColumn->setFixedWidth(250);
            lblNameColumn->setText(QString::fromStdString(s));
            displayColumn->addWidget(lblNameColumn);
            QPushButton *buttonAddWord = new QPushButton;
            buttonAddWord->setText("+");
            buttonAddWord->setFixedWidth(250);
            layoutForButtonAddWord->addWidget(buttonAddWord);
            // TODO create function to add a word.
        }

        QPushButton *validButton = new QPushButton;
        validButton->setText("Ajouter le mot");
        validButton->setFixedWidth(250);
        newQVBoxLayout->addWidget(validButton);
    }
    file.close();
}

void NewVocab::saveColumnName(){
    for(QLineEdit* lineEdit : listLineEdit){
        listNameColumn.push_back(lineEdit->text().toStdString());
    }
}

bool NewVocab::verifLineEdit(){
    errorLabelForNameColumn->setText("");
    for(QLineEdit* lineEdit:listLineEdit){
        if(lineEdit->text() == ""){
            errorLabelForNameColumn->setText("Un des champs n'est pas rempli.");
        }
    }

    return true;
}

void NewVocab::clearLayout(QLayout *layout){
    for(int i=0; i<layout->count();i++){
        delete layout->takeAt(i)->widget();
    }
    QLayoutItem *item;
     while ((item = layout->takeAt(0))){
        item->widget()->deleteLater();
     }
}

NewVocab::~NewVocab()
{
    delete ui;
}

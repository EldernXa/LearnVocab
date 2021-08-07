#include "modifyword.h"
#include "ui_modifyword.h"

ModifyWord::ModifyWord(string nameVocab, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyWord)
{
    ui->setupUi(this);
    this->nameVocab = nameVocab;
    readerVocab = new ReaderVocab(nameVocab);
    ui->widget->setLayout(new QVBoxLayout);
    QWidget *widgetForNameColumn = new QWidget;
    ui->widget->layout()->addWidget(widgetForNameColumn);
    QHBoxLayout *layoutForNameColumns = new QHBoxLayout(widgetForNameColumn);
    for(auto &nameColumn : readerVocab->getColumnName()){
        QLabel *lblNameColumn = new QLabel;
        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setAlignment(Qt::AlignCenter);
        layoutForNameColumns->addWidget(lblNameColumn);
    }
    layoutForNameColumns->addWidget(new QLabel);
    QFrame *frameVLine = new QFrame;
    ui->widget->layout()->addWidget(frameVLine);
    frameVLine->setFrameShape(QFrame::HLine);

    for(unsigned int i=0; i<readerVocab->getAllLineOfTheVocab().size(); i++){
        listLineEditForWord.push_back(vector<vector<QLineEdit*>>());
        bool verifIsKnown = readerVocab->isLineVocabKnown(i);
        listIsKnown.push_back(verifIsKnown);
        vector<string> valueToDisplay = readerVocab->getLineSplited(i);
        QWidget *widgetForNameWord = new QWidget;
        ui->widget->layout()->addWidget(widgetForNameWord);
        QHBoxLayout *layoutForNameWord = new QHBoxLayout(widgetForNameWord);
        unsigned int multiply_value = 1;
        for(unsigned int j = 0; j<valueToDisplay.size(); j++){
            listLineEditForWord.at(i).push_back(vector<QLineEdit*>());
            vector<string> differentValueForAWord = readerVocab->getWordSplitedFromLineSplited(i, j);
            if(differentValueForAWord.size()>1){
                QWidget *widgetForAWord = new QWidget;
                QVBoxLayout *layoutForAWord = new QVBoxLayout(widgetForAWord);
                if(differentValueForAWord.size()>multiply_value){
                    multiply_value = differentValueForAWord.size();
                }

                for(auto &word : differentValueForAWord){
                    QLineEdit *lineEdit = new QLineEdit;
                    lineEdit->setText(QString::fromStdString(word));
                    layoutForAWord->addWidget(lineEdit);
                    listLineEditForWord.at(i).at(j).push_back(lineEdit);
                }
                layoutForNameWord->addWidget(widgetForAWord);
            }else{
                QLineEdit *lineEdit = new QLineEdit;
                lineEdit->setText(QString::fromStdString(valueToDisplay.at(j)));
                layoutForNameWord->addWidget(lineEdit);
                listLineEditForWord.at(i).at(j).push_back(lineEdit);
            }
        }
        QWidget *widgetForButton = new QWidget;
        QVBoxLayout *layoutButton = new QVBoxLayout(widgetForButton);
        QPushButton *buttonDelete = new QPushButton;
        setDeleteIcon(buttonDelete);
        layoutButton->addWidget(buttonDelete);
        QPushButton *buttonChange = new QPushButton;
        if(verifIsKnown){
            setGreenCheckIcon(buttonChange);
        }else{
            setRedCrossIcon(buttonChange);
        }
        listButtonChangeState.push_back(buttonChange);
        connect(buttonDelete, &QPushButton::clicked, this, [this, i]{deletingWord(i);});
        connect(buttonChange, &QPushButton::clicked, this, [this, i]{changeStateWord(i);});
        layoutButton->addWidget(buttonChange);
        layoutForNameWord->addWidget(widgetForButton);
        QFrame *frameLine = new QFrame;
        ui->widget->layout()->addWidget(frameLine);
        frameLine->setFrameShape(QFrame::HLine);
        QSpacerItem *itemSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
        ui->widget->layout()->addItem(itemSpacer);
    }
}

void ModifyWord::deletingWord(int i){
    cout << "deleting word." << endl;
}

void ModifyWord::changeStateWord(int i){
    // cout << "changing state of a word" << endl;
    if(listIsKnown.at(i)){
        setRedCrossIcon(listButtonChangeState.at(i));
        listIsKnown.at(i) = false;
    }else{
        setGreenCheckIcon(listButtonChangeState.at(i));
        listIsKnown.at(i) = true;
    }
}

void ModifyWord::setDeleteIcon(QPushButton* buttonWeWantToSetIcon){
    buttonWeWantToSetIcon->setIcon(QIcon(QPixmap(":/logoImg/delete")));
}

void ModifyWord::setGreenCheckIcon(QPushButton* buttonWeWantToSetIcon){
    buttonWeWantToSetIcon->setIcon(QIcon(QPixmap(":/logoImg/greenCheck")));
}

void ModifyWord::setRedCrossIcon(QPushButton* buttonWeWantToSetIcon){
    buttonWeWantToSetIcon->setIcon(QIcon(QPixmap(":/logoImg/redCross")));
}

vector<string> ModifyWord::split(const std::string& s, char delimiter){
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while(getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}

ModifyWord::~ModifyWord()
{
    delete ui;
}

void ModifyWord::on_buttonConfirmModify_clicked(){
    vector<vector<vector<string>>> listWord;
    for(unsigned int i=0 ; i<listLineEditForWord.size(); i++){
        listWord.push_back(vector<vector<string>>());
        for(unsigned int j=0; j<listLineEditForWord.at(i).size(); j++){
            listWord.at(i).push_back(vector<string>());
            for(QLineEdit* lineEdit : listLineEditForWord.at(i).at(j)){
                listWord.at(i).at(j).push_back(lineEdit->text().toStdString());
            }
        }
    }
    new WriterVocab(nameVocab, readerVocab->getNumberOfColumns(), readerVocab->getColumnName(), listWord, listIsKnown);
}

void ModifyWord::on_buttonBack_clicked(){
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

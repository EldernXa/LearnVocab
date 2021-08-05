#include "modifyword.h"
#include "ui_modifyword.h"

ModifyWord::ModifyWord(string nameVocab, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyWord)
{
    ui->setupUi(this);
    this->nameVocab = nameVocab;
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

void ModifyWord::on_buttonBack_clicked(){
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

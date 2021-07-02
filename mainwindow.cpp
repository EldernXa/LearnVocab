#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuVocab->setEnabled(false);
    QWidget *scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout(new QVBoxLayout);
    //ui->scrollArea->setLayout(new QVBoxLayout);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollAreaContent);
    getVocab();
    enableEvent();
}

void MainWindow::getVocab(){
    std::set<std::filesystem::path> sorted_by_name;
    for (const auto & entry : std::filesystem::directory_iterator("./")){
        std::vector<std::string> list = split(entry.path().generic_string(), '.');
        if(list.at(list.size()-1).compare("vocab") == 0){
            QPushButton *pushButton = new QPushButton;
            std::string newString = split(entry.path().generic_string(), '/').at(1);
            std::string lastString = split(newString, '.').at(0);
            pushButton->setText(QString::fromStdString(lastString));
            ui->scrollArea->widget()->layout()->addWidget(pushButton);
            listButtonForVocab.push_back(pushButton);
            pushButton->setCheckable(true);
            connect(pushButton, &QPushButton::clicked, this, [this, pushButton]{clickButtonVocab(pushButton);});
        }
    }
}

void MainWindow::clickButtonVocab(QPushButton *pushButton){
    if(pushButton->isChecked()){
        for(auto *btn : listButtonForVocab){
            if(btn!=pushButton){
                btn->setChecked(false);
            }
        }
        ui->menuVocab->setEnabled(true);
    }else{
        ui->menuVocab->setEnabled(false);
    }
}

std::vector<std::string> MainWindow::split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

void MainWindow::enableEvent(){
    connect(ui->saveNewVocab, SIGNAL(clicked()), this, SLOT(newVocab()));
    connect(ui->actionDisplayList, SIGNAL(triggered()), this, SLOT(displayVocab()));
}

void MainWindow::newVocab(){
    if(actualOtherWindow!=nullptr){
        actualOtherWindow->close();
        actualOtherWindow = nullptr;
    }
    NewVocab *newVocab = new NewVocab(this);
    newVocab->show();
    actualOtherWindow = newVocab;
}

void MainWindow::displayVocab(){
    if(actualOtherWindow!=nullptr){
        actualOtherWindow->close();
        actualOtherWindow = nullptr;
    }
    DisplayVocab *displayVocab = new DisplayVocab(getNameVocab(), this);
    displayVocab->show();
    actualOtherWindow = displayVocab;
}

std::string MainWindow::getNameVocab(){
    for(auto &button : listButtonForVocab){
        if(button->isChecked()){
            return button->text().toStdString();
        }
    }
    return nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}
























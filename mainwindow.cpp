#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enableEvent();
    QWidget *scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout(new QVBoxLayout);
    //ui->scrollArea->setLayout(new QVBoxLayout);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollAreaContent);
    getVocab();
}

void MainWindow::getVocab(){
    std::set<std::filesystem::path> sorted_by_name;
    for (const auto & entry : std::filesystem::directory_iterator("./")){
            //std::cout << entry.path() << std::endl;
            //sorted_by_name.insert(entry.path());
        std::vector<std::string> list = split(entry.path().generic_string(), '.');
        if(list.at(list.size()-1).compare("vocab") == 0){
            QPushButton *pushButton = new QPushButton;
            std::string newString = split(entry.path().generic_string(), '/').at(1);
            std::string lastString = split(newString, '.').at(0);
            pushButton->setText(QString::fromStdString(lastString));
            ui->scrollArea->widget()->layout()->addWidget(pushButton);
        }
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
    connect(ui->saveNewVocab, SIGNAL(clicked()), this, SLOT(newfunction()));
}

void MainWindow::newfunction(){
    NewVocab *newVocab = new NewVocab(this);
    newVocab->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enableEvent();
    ui->scrollArea->setLayout(new QVBoxLayout);
    QPushButton *pushButton1 = new QPushButton;
    pushButton1->setText("okok");
    QPushButton *pushButton2 = new QPushButton;
    pushButton2->setText("ddd");
    ui->scrollArea->layout()->addWidget(pushButton1);
    ui->scrollArea->layout()->addWidget(pushButton2);
    getVocab();
}

void MainWindow::getVocab(){
    std::set<std::filesystem::path> sorted_by_name;
    for (const auto & entry : std::filesystem::directory_iterator("./")){
            //std::cout << entry.path() << std::endl;
            //sorted_by_name.insert(entry.path());
        QPushButton *pushButton = new QPushButton;
        pushButton->setText(QString::fromStdString(entry.path().generic_string()));
        ui->scrollArea->layout()->addWidget(pushButton);
    }

//    for(std::filesystem::path path : sorted_by_name){
//        std::string te = path.generic_string();
//        std::vector<std::string> list = split(te, '.');
//        //std::cout << list.at(list.size()-1) << std::endl;
//        if(list.at(list.size()-1).compare("jpg") == 0 ||
//                list.at(list.size()-1).compare("png")==0){
//            //listPathPicture.push_back(te);
//        }
//    }
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


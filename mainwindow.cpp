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

    ui->widget->getScrollArea()->setLayout(new QVBoxLayout);
    //ui->scrollArea->setLayout(new QVBoxLayout);
    ui->widget->getScrollArea()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->widget->getScrollArea()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->widget->getScrollArea()->setWidgetResizable(true);
    ui->widget->getScrollArea()->setWidget(scrollAreaContent);


//    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    ui->scrollArea->setWidgetResizable(true);
//    ui->scrollArea->setWidget(scrollAreaContent);
    getVocab(ui->widget->getScrollArea());
    enableEvent();
}

void MainWindow::getVocab(QScrollArea *scrollArea){
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir("./")) != NULL){
        while((ent = readdir(dir)) != NULL){
            std::vector<std::string> list = split(ent->d_name, '.');
            if(list.at(list.size()-1).compare("vocab") == 0){
                QPushButton *pushButton = new QPushButton;
                string lastString = split(ent->d_name, '.').at(0);
                pushButton->setText(QString::fromStdString(lastString));
                scrollArea->layout()->addWidget(pushButton);
                listButtonForVocab.push_back(pushButton);
                pushButton->setCheckable(true);
                connect(pushButton, &QPushButton::clicked, this, [this, pushButton]{clickButtonVocab(pushButton);});
            }
        }
        closedir(dir);
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
    connect(ui->widget->getButtonSaveNewVocab(), SIGNAL(clicked()), this, SLOT(newVocab()));
    //connect(ui->saveNewVocab, SIGNAL(clicked()), this, SLOT(newVocab()));
    connect(ui->actionDisplayList, SIGNAL(triggered()), this, SLOT(displayVocab()));
    connect(ui->actionRandomNWord, SIGNAL(triggered()), this, SLOT(quizVocab()));
}

void MainWindow::quizVocab(){
//    if(actualOtherWindow!=nullptr){
//        actualOtherWindow->close();
//        actualOtherWindow = nullptr;
//    }
//    QuizVocab * quizVocab = new QuizVocab(getNameVocab(), QuizVocab::QuizType::randomNWord, this);
//    quizVocab->show();
//    actualOtherWindow = quizVocab;
    clearLayout(ui->widget->layout());

    WidgetQuizVocab *widgetQuizVocab = new WidgetQuizVocab(getNameVocab(), WidgetQuizVocab::randomNWord);
    ui->widget->layout()->addWidget(widgetQuizVocab);
    ui->menuVocab->setEnabled(false);
}

void MainWindow::newVocab(){
    // TODO find a way to delete class after uses.
    clearLayout(ui->widget->layout());

    WidgetNewVocab *widgetNewVocab = new WidgetNewVocab;
    ui->widget->layout()->addWidget(widgetNewVocab);
    ui->menuVocab->setEnabled(false);
    connect(widgetNewVocab, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));


//    if(actualOtherWindow!=nullptr){
//        actualOtherWindow->close();
//        actualOtherWindow = nullptr;
//    }
//    NewVocab *newVocab = new NewVocab(this);
//    newVocab->show();
//    actualOtherWindow = newVocab;
}

void MainWindow::displayVocab(){
    clearLayout(ui->widget->layout());

    ui->widget->layout()->addWidget(new WidgetDisplayVocab(getNameVocab()));
    ui->menuVocab->setEnabled(false);
//    if(actualOtherWindow!=nullptr){
//        actualOtherWindow->close();
//        actualOtherWindow = nullptr;
//    }
//    DisplayVocab *displayVocab = new DisplayVocab(getNameVocab(), this);
//    displayVocab->show();
//    actualOtherWindow = displayVocab;
}

void MainWindow::restoreMainWidget(){
    clearLayout(ui->widget->layout());
    WidgetMainWindow *widgetMainWindow = new WidgetMainWindow;
    ui->widget->layout()->addWidget(widgetMainWindow);

    QWidget *scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout(new QVBoxLayout);

    widgetMainWindow->getScrollArea()->setLayout(new QVBoxLayout);
    widgetMainWindow->getScrollArea()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widgetMainWindow->getScrollArea()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    widgetMainWindow->getScrollArea()->setWidgetResizable(true);
    widgetMainWindow->getScrollArea()->setWidget(scrollAreaContent);

    getVocab(widgetMainWindow->getScrollArea());
}

std::string MainWindow::getNameVocab(){
    for(auto &button : listButtonForVocab){
        if(button->isChecked()){
            return button->text().toStdString();
        }
    }
    return nullptr;
}

void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

MainWindow::~MainWindow()
{
    //delete actualOtherWindow;
    delete ui;
}
























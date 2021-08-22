#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    disablingMenu();
    QWidget *scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout(new QVBoxLayout);
    this->setWindowTitle(QString("LearnVocab (v.%1)").arg(QString::fromStdString(NUM_VERSION)));

    ui->widget->getScrollArea()->setLayout(new QVBoxLayout);
    ui->widget->getScrollArea()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->widget->getScrollArea()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->widget->getScrollArea()->setWidgetResizable(true);
    ui->widget->getScrollArea()->setWidget(scrollAreaContent);
    getVocab(ui->widget->getScrollArea());
    enableEvent();
}

void MainWindow::disablingMenu(){
    ui->menuVocab->setEnabled(false);
    ui->menuModification->setEnabled(false);
}

void MainWindow::enablingMenu(){
    ui->menuVocab->setEnabled(true);
    ui->menuModification->setEnabled(true);
}

void MainWindow::getVocab(QScrollArea *scrollArea){
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(CstStatic::getPathToVocabFile().c_str())) != NULL){
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
        enablingMenu();
    }else{
        disablingMenu();
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
    connect(ui->actionDisplayList, SIGNAL(triggered()), this, SLOT(displayVocab()));
    connect(ui->actionAddWord, SIGNAL(triggered()), this, SLOT(addWordIntoVocab()));
    connect(ui->actionRemoveWord, SIGNAL(triggered()), this, SLOT(removeWordFromVocab()));
    connect(ui->actionModifyAWord, SIGNAL(triggered()), this, SLOT(modifyVocab()));
    connect(ui->actionRemoveVoc, SIGNAL(triggered()), this, SLOT(removeVocab()));

    // ---------------- action for quiz -----------------
    connect(ui->actionRandomNWord, SIGNAL(triggered()), this, SLOT(quizVocab()));
    connect(ui->actionRandomNWordKnow, SIGNAL(triggered()), this, SLOT(quizVocabNWordKnow()));
    connect(ui->actionRandomNWordNotKnow, SIGNAL(triggered()), this, SLOT(quizVocabNWordNotKnow()));
    connect(ui->actionNFirstWordKnow, SIGNAL(triggered()), this, SLOT(quizVocabNFirstWordKnow()));
    connect(ui->actionNFirstWordNotKnow, SIGNAL(triggered()), this, SLOT(quizVocabNFirstWordNotKnow()));


}

void MainWindow::removeVocab(){
    int rep = QMessageBox::warning(this, tr("Supprimer le vocabulaire"),
                                    tr("Voulez-vous vraiment supprimer le vocabulaire %1 ?").arg(QString::fromStdString(getNameVocab())),
                                    QMessageBox::Yes, QMessageBox::No);
    if(rep == QMessageBox::Yes){
        // TODO change there.
        QDir().remove(QString::fromStdString(CstStatic::getPathToVocabFile()+getNameVocab()+CstStatic::getFormatVocabFile()));
        disablingMenu();
        listButtonForVocab.clear();
        clearLayout(ui->widget->layout());
        restoreMainWidget();
    }
}

void MainWindow::addWordIntoVocab(){
    clearLayout(ui->widget->layout());

    AddWord *addWord = new AddWord(getNameVocab());
    ui->widget->layout()->addWidget(addWord);
    disablingMenu();
    listButtonForVocab.clear();
    connect(addWord, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::removeWordFromVocab(){
    clearLayout(ui->widget->layout());

    RemoveWord *removeWord = new RemoveWord(getNameVocab());
    ui->widget->layout()->addWidget(removeWord);
    disablingMenu();
    listButtonForVocab.clear();
    connect(removeWord, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::modifyVocab(){
    clearLayout(ui->widget->layout());

    ModifyWord *modifyWord = new ModifyWord(getNameVocab());
    ui->widget->layout()->addWidget(modifyWord);
    disablingMenu();
    listButtonForVocab.clear();
    connect(modifyWord, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::quizVocab(){
    clearLayout(ui->widget->layout());

    WidgetQuizVocab *widgetQuizVocab = new WidgetQuizVocab(getNameVocab(), WidgetQuizVocab::randomNWord);
    ui->widget->layout()->addWidget(widgetQuizVocab);
    disablingMenu();
    listButtonForVocab.clear();
    connect(widgetQuizVocab, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::quizVocabNWordKnow(){
    clearLayout(ui->widget->layout());

    WidgetQuizVocab *widgetQuizVocab = new WidgetQuizVocab(getNameVocab(), WidgetQuizVocab::NRandomWordKnow);
    ui->widget->layout()->addWidget(widgetQuizVocab);
    disablingMenu();
    listButtonForVocab.clear();
    connect(widgetQuizVocab, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::quizVocabNWordNotKnow(){
    clearLayout(ui->widget->layout());

    WidgetQuizVocab *widgetQuizVocab = new WidgetQuizVocab(getNameVocab(), WidgetQuizVocab::NRandomWordNotKnow);
    ui->widget->layout()->addWidget(widgetQuizVocab);
    disablingMenu();
    listButtonForVocab.clear();
    connect(widgetQuizVocab, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::quizVocabNFirstWordKnow(){
    clearLayout(ui->widget->layout());

    WidgetQuizVocab *widgetQuizVocab = new WidgetQuizVocab(getNameVocab(), WidgetQuizVocab::NFirstWordKnow);
    ui->widget->layout()->addWidget(widgetQuizVocab);
    disablingMenu();
    listButtonForVocab.clear();
    connect(widgetQuizVocab, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::quizVocabNFirstWordNotKnow(){
    clearLayout(ui->widget->layout());

    WidgetQuizVocab *widgetQuizVocab = new WidgetQuizVocab(getNameVocab(), WidgetQuizVocab::NFirstWordNotKnow);
    ui->widget->layout()->addWidget(widgetQuizVocab);
    disablingMenu();
    listButtonForVocab.clear();
    connect(widgetQuizVocab, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::newVocab(){
    // TODO find a way to delete class after uses.
    clearLayout(ui->widget->layout());

    WidgetNewVocab *widgetNewVocab = new WidgetNewVocab;
    ui->widget->layout()->addWidget(widgetNewVocab);
    disablingMenu();
    listButtonForVocab.clear();
    connect(widgetNewVocab, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
}

void MainWindow::displayVocab(){
    clearLayout(ui->widget->layout());

    WidgetDisplayVocab *widgetDisplayVocab = new WidgetDisplayVocab(getNameVocab());
    ui->widget->layout()->addWidget(widgetDisplayVocab);
    disablingMenu();
    listButtonForVocab.clear();
    connect(widgetDisplayVocab, SIGNAL(destroyed()), this, SLOT(restoreMainWidget()));
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
    delete ui;
}
























#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <set>
#include <dirent.h>

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>

#include "widgetmainwindow.h"
#include "widgetdisplayvocab.h"
#include "widgetnewvocab.h"
#include "widgetquizvocab.h"
#include "addword.h"
#include "removeword.h"
#include "modifyword.h"
#include "CstFile/cststatic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void enableEvent();
    void getVocab(QScrollArea*);
    void clickButtonVocab(QPushButton *);
    std::vector<std::string> split(const std::string&, char);
    std::string getNameVocab();
    void clearLayout(QLayout*, bool deleteWidgets = true);
    void enablingMenu();
    void disablingMenu();

    Ui::MainWindow *ui;
    std::vector<QPushButton*> listButtonForVocab;
    string const NUM_VERSION = "1.3.1";

private slots :
    void newVocab();
    void displayVocab();
    void quizVocab();
    void quizVocabNWordKnow();
    void quizVocabNWordNotKnow();
    void quizVocabNFirstWordKnow();
    void quizVocabNFirstWordNotKnow();
    void addWordIntoVocab();
    void modifyVocab();
    void removeWordFromVocab();
    void restoreMainWidget();
};
#endif // MAINWINDOW_H

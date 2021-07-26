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

    Ui::MainWindow *ui;
    std::vector<QPushButton*> listButtonForVocab;
    string const NUM_VERSION = "1.1.1";

private slots :
    void newVocab();
    void displayVocab();
    void quizVocab();
    void restoreMainWidget();
};
#endif // MAINWINDOW_H

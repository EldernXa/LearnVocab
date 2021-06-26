#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <filesystem>
#include <set>

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>

#include "newvocab.h"

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
    void getVocab();
    std::vector<std::string> split(const std::string&, char);

    Ui::MainWindow *ui;

private slots :
    void newfunction();
};
#endif // MAINWINDOW_H

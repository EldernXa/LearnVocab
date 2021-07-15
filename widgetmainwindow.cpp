#include "widgetmainwindow.h"
#include "ui_widgetmainwindow.h"

WidgetMainWindow::WidgetMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMainWindow)
{
    ui->setupUi(this);
}

QScrollArea *WidgetMainWindow::getScrollArea(){
    return ui->scrollArea;
}

QPushButton *WidgetMainWindow::getButtonSaveNewVocab(){
    return ui->pushButton;
}

WidgetMainWindow::~WidgetMainWindow()
{
    delete ui;
}

#ifndef WIDGETMAINWINDOW_H
#define WIDGETMAINWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>

namespace Ui {
class WidgetMainWindow;
}

class WidgetMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMainWindow(QWidget *parent = nullptr);
    ~WidgetMainWindow();
    QScrollArea *getScrollArea();
    QPushButton *getButtonSaveNewVocab();

private:
    Ui::WidgetMainWindow *ui;
};

#endif // WIDGETMAINWINDOW_H

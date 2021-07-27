#ifndef WIDGETDISPLAYVOCAB_H
#define WIDGETDISPLAYVOCAB_H

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

#include "readervocab.h"

using namespace std;

namespace Ui {
class WidgetDisplayVocab;
}

class WidgetDisplayVocab : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetDisplayVocab(string nameVocab, QWidget *parent = nullptr);
    ~WidgetDisplayVocab();
    static const int WIDTH_LABEL = 150;
    static const int HEIGHT_LABEL = 30;
    static const int LIMIT_WIDGET = 5;
    static const int HEIGHT_WIDGET = 30 * LIMIT_WIDGET;

private slots:
    void on_buttonBack_clicked();

private:
    vector<string> split(const string&, char delimiter);

    ReaderVocab *readerVocab = nullptr;
    string nameVocabToDisplay;
    QScrollArea *scrollArea;

    Ui::WidgetDisplayVocab *ui;
};

#endif // WIDGETDISPLAYVOCAB_H

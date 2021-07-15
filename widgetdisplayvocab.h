#ifndef WIDGETDISPLAYVOCAB_H
#define WIDGETDISPLAYVOCAB_H

#include <fstream>
#include <iostream>
#include <filesystem>
#include <set>

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

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

private:
    vector<string> split(const string&, char delimiter);

    string nameVocabToDisplay;
    int numberOfColumn;
    int lastHeight = 0;
    vector<string> nameColumns;
    const int WIDTH_LABEL = 150;
    const int HEIGHT_LABEL = 30;
    const int LIMIT_WIDGET = 5;
    const int HEIGHT_WIDGET = 30 * LIMIT_WIDGET;
    QScrollArea *scrollArea;

    fstream fileToDisplayVocab;

    Ui::WidgetDisplayVocab *ui;
};

#endif // WIDGETDISPLAYVOCAB_H
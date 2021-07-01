#ifndef DISPLAYVOCAB_H
#define DISPLAYVOCAB_H

#include <fstream>
#include <iostream>
#include <filesystem>
#include <set>

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

using namespace std;


class DisplayVocab : public QMainWindow
{
    Q_OBJECT
public:
    explicit DisplayVocab(std::string nameVocab, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *qresizeEvent) override;

private:
    vector<string> split(const string&, char delimiter);

    string nameVocabToDisplay;
    int numberOfColumn;
    int lastHeight=0;
    vector<string> nameColumns;
    const int WIDTH_LABEL = 70;
    const int HEIGHT_LABEL = 30;
    const int LIMIT_WIDGET = 5;
    const int HEIGHT_WIDGET = 30*LIMIT_WIDGET;

    fstream fileToDisplayVocab;

    QScrollArea *scrollArea;

signals:

};

#endif // DISPLAYVOCAB_H

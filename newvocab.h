#ifndef NEWVOCAB_H
#define NEWVOCAB_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

#include <QMainWindow>
#include <QRect>
#include <QResizeEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class NewVocab;
}

class NewVocab : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewVocab(QWidget *parent = nullptr);
    ~NewVocab();

protected:
    void resizeEvent(QResizeEvent *qresizeEvent);

private:
    void enableEvent();
    void clearLayout(QLayout *layout);
    bool verifLineEdit();
    void saveColumnName();

    std::vector<QLineEdit*> listLineEdit;
    std::vector<std::string> listNameColumn;
    std::vector<std::vector<QLineEdit *>> listLineEditForWord;
    int numberOfColumn;
    std::string nameVocab;
    QLabel *errorLabelForNameColumn = new QLabel;
    Ui::NewVocab *ui;

private slots:
    void runFirstButton();
    void valideNameColumn();
};

#endif // NEWVOCAB_H

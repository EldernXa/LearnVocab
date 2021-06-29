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
#include <QDebug>

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
    void resizeEvent(QResizeEvent *qresizeEvent) override;

private:
    void enableEvent();
    void clearLayout(QLayout *layout);
    bool verifLineEdit();
    void saveColumnName();
    void addingWord(int num);
    void removeWord(int num);
    void closeEvent(QCloseEvent*) override;

    QPushButton *finishButton = nullptr;
    std::vector<QLineEdit*> listLineEdit;
    std::vector<std::string> listNameColumn;
    std::vector<std::vector<QLineEdit *>*> listLineEditForWord;
    std::vector<QVBoxLayout *> listVBoxLayoutForListWord;
    std::vector<QPushButton *> listQPushButtonAdd;
    std::vector<QPushButton *> listQPushButtonRemove;
    int numberOfColumn;
    bool addWord = false;
    std::string nameVocab;
    QLabel *errorLabelForNameColumn = new QLabel;
    QLabel *errorInsertingWord = nullptr;
    Ui::NewVocab *ui;
    std::fstream fileToSaveVocab;

    QLabel *lblLastWord = nullptr;

    const int WIDTH_LINE_EDIT_WORD = 40;
    const int HEIGHT_LINE_EDIT_WORD = 40;
    const int WIDTH_WIDGET = 250;
    const int HEIGHT_WIDGET = 20;
    const unsigned int LIMIT_NUMBER_WORD = 5;

private slots:
    void runFirstButton();
    void valideNameColumn();
    void saveWord();
    void finishVocab();
};

#endif // NEWVOCAB_H

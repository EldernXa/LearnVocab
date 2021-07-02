#ifndef QUIZVOCAB_H
#define QUIZVOCAB_H

#include <QMainWindow>

namespace Ui {
class QuizVocab;
}

class QuizVocab : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuizVocab(std::string, QWidget *parent = nullptr);
    ~QuizVocab();

private:
    Ui::QuizVocab *ui;
    std::string nameVocab;
};

#endif // QUIZVOCAB_H

#ifndef NEWVOCAB_H
#define NEWVOCAB_H

#include <iostream>

#include <QMainWindow>
#include <QRect>
#include <QResizeEvent>
#include <QPushButton>

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

    Ui::NewVocab *ui;
private slots:
    void runFirstButton();
};

#endif // NEWVOCAB_H

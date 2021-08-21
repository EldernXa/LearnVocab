#ifndef WIDGETNEWVOCABSECONDSTEP_H
#define WIDGETNEWVOCABSECONDSTEP_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class WidgetNewVocabSecondStep;
}

class WidgetNewVocabSecondStep : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNewVocabSecondStep(QWidget *parent = nullptr);
    ~WidgetNewVocabSecondStep();

    QLineEdit *getFirstLineEdit();
    QLineEdit *getSecondLineEdit();
    QPushButton *getValidButton();
    QLabel *getErrorLabel();
    QLabel *getLblNameColumn();
    void addWidgetToLayout(QWidget*);

private:
    Ui::WidgetNewVocabSecondStep *ui;
};

#endif // WIDGETNEWVOCABSECONDSTEP_H

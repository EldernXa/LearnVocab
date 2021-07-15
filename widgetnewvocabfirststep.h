#ifndef WIDGETNEWVOCABFIRSTSTEP_H
#define WIDGETNEWVOCABFIRSTSTEP_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class WidgetNewVocabFirstStep;
}

class WidgetNewVocabFirstStep : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNewVocabFirstStep(QWidget *parent = nullptr);
    ~WidgetNewVocabFirstStep();
    QPushButton *getButton();
    QLabel *getLabelError();
    QLineEdit *getLineEditForName();
    QLineEdit *getLineEditNumberOfColumn();

private:
    Ui::WidgetNewVocabFirstStep *ui;
};

#endif // WIDGETNEWVOCABFIRSTSTEP_H

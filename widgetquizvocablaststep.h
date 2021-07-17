#ifndef WIDGETQUIZVOCABLASTSTEP_H
#define WIDGETQUIZVOCABLASTSTEP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class WidgetQuizVocabLastStep;
}

class WidgetQuizVocabLastStep : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetQuizVocabLastStep(QWidget *parent = nullptr);
    ~WidgetQuizVocabLastStep();
    QHBoxLayout* getLayoutNameColumn();
    QHBoxLayout* getLayoutForQLineEdit();
    QPushButton* getConfirmButton();
    QLabel* getNumberWordMissing();
    QPushButton* getNextWordBtn();

private:
    Ui::WidgetQuizVocabLastStep *ui;
};

#endif // WIDGETQUIZVOCABLASTSTEP_H

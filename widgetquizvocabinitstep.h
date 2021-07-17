#ifndef WIDGETQUIZVOCABINITSTEP_H
#define WIDGETQUIZVOCABINITSTEP_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class WidgetQuizVocabInitStep;
}

class WidgetQuizVocabInitStep : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetQuizVocabInitStep(QWidget *parent = nullptr);
    ~WidgetQuizVocabInitStep();
    QLabel* getLblTitle();
    QLabel* getLblMaxWord();
    QLabel* getLblError();
    QLineEdit* getLineEditForMaxWord();
    QPushButton* getValidButton();

private:
    Ui::WidgetQuizVocabInitStep *ui;
};

#endif // WIDGETQUIZVOCABINITSTEP_H

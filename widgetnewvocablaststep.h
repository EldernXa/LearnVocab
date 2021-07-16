#ifndef WIDGETNEWVOCABLASTSTEP_H
#define WIDGETNEWVOCABLASTSTEP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class WidgetNewVocabLastStep;
}

class WidgetNewVocabLastStep : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNewVocabLastStep(QWidget *parent = nullptr);
    ~WidgetNewVocabLastStep();

    QHBoxLayout* getLayoutForAddingBtn();
    QHBoxLayout* getLayoutForNameColumn();
    QHBoxLayout* getLayoutForQLineEdit();
    QHBoxLayout* getLayoutForRemovingBtn();
    QPushButton* getBtnAddWord();
    QPushButton* getConfirmBtn();
    QLabel* getLblLastWord();
    QLabel* getLblError();

private:
    Ui::WidgetNewVocabLastStep *ui;
};

#endif // WIDGETNEWVOCABLASTSTEP_H

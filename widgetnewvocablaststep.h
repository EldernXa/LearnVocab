#ifndef WIDGETNEWVOCABLASTSTEP_H
#define WIDGETNEWVOCABLASTSTEP_H

#include <QWidget>
#include <QHBoxLayout>

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

private:
    Ui::WidgetNewVocabLastStep *ui;
};

#endif // WIDGETNEWVOCABLASTSTEP_H

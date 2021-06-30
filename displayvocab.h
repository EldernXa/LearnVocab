#ifndef DISPLAYVOCAB_H
#define DISPLAYVOCAB_H

#include <QMainWindow>

class DisplayVocab : public QMainWindow
{
    Q_OBJECT
public:
    explicit DisplayVocab(std::string nameVocab, QWidget *parent = nullptr);

signals:

};

#endif // DISPLAYVOCAB_H

#ifndef GLOBALFCT_H
#define GLOBALFCT_H

#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class GlobalFct
{
public:
    GlobalFct();
    void static changeSizeFontOfLbl(QLabel*, QSize);
    void static changeSizeFontOfLineEdit(QLineEdit*, QSize);
    void static changeSizeFontOfPushButton(QPushButton*, QSize);

private:
    int static getNewSizeFont(int, int);



    int static const CST_LIMIT_SIZE = 25;
};

#endif // GLOBALFCT_H

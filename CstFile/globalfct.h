#ifndef GLOBALFCT_H
#define GLOBALFCT_H

#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QLineEdit>

class GlobalFct
{
public:
    GlobalFct();
    void static changeSizeFontOfLbl(QLabel*, int, int);
    void static changeSizeFontOfLineEdit(QLineEdit*, int, int);

private:
    int static getNewSizeFont(int, int);



    int static const CST_LIMIT_SIZE = 25;
};

#endif // GLOBALFCT_H

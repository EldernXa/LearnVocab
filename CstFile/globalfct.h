#ifndef GLOBALFCT_H
#define GLOBALFCT_H

#include <QApplication>
#include <QScreen>

class GlobalFct
{
public:
    GlobalFct();
    int static getNewSizeFont(int, int);

private:
    int static const CST_LIMIT_SIZE = 25;
};

#endif // GLOBALFCT_H

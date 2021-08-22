#ifndef GLOBALFCT_H
#define GLOBALFCT_H

#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class GlobalFct
{
public:
    GlobalFct();
    void static changeSizeFontOfLbl(QLabel*, QSize);
    void static changeSizeFontOfLineEdit(QLineEdit*, QSize);
    void static changeSizeFontOfPushButton(QPushButton*, QSize);
    bool static compareString(string toCompare, string comparaison);

private:
    int static getNewSizeFont(int, int);
    string static ltrim(const string &);
    string static rtrim(const string &);
    string static trim(const string &);



    int static const CST_LIMIT_SIZE = 25;
};

#endif // GLOBALFCT_H

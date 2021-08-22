#include "globalfct.h"

const std::string WHITESPACE = " \n\r\t\f\v";

GlobalFct::GlobalFct()
{}

int GlobalFct::getNewSizeFont(int width, int height){
    return std::max(CST_LIMIT_SIZE - (qApp->screens()[0]->size().width()*0.01 - width*0.01),
            CST_LIMIT_SIZE - (qApp->screens()[0]->size().height()*0.01 - height * 0.01));
}

void GlobalFct::changeSizeFontOfLbl(QLabel *lbl, QSize size){
    QFont font = lbl->font();
    font.setPointSize(getNewSizeFont(size.width(), size.height()));
    lbl->setFont(font);
}

void GlobalFct::changeSizeFontOfLineEdit(QLineEdit *lineEdit, QSize size){
    QFont font = lineEdit->font();
    font.setPointSize(getNewSizeFont(size.width(), size.height()));
    lineEdit->setFont(font);
}

void GlobalFct::changeSizeFontOfPushButton(QPushButton *btn, QSize size){
    QFont font = btn->font();
    font.setPointSize(getNewSizeFont(size.width(), size.height()));
    btn->setFont(font);
}

bool GlobalFct::compareString(string toCompare, string comparaison){
    return trim(toCompare).compare(trim(comparaison)) == 0;
}

string GlobalFct::ltrim(const string &s){
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string GlobalFct::rtrim(const string &s){
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end+1);
}

string GlobalFct::trim(const string &s){
    return rtrim(ltrim(s));
}



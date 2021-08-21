#include "globalfct.h"

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



#include "globalfct.h"

GlobalFct::GlobalFct()
{}

int GlobalFct::getNewSizeFont(int width, int height){
    return std::max(CST_LIMIT_SIZE - (qApp->screens()[0]->size().width()*0.01 - width*0.01),
            CST_LIMIT_SIZE - (qApp->screens()[0]->size().height()*0.01 - height * 0.01));
}



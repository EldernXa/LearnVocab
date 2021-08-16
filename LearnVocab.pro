QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addword.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyword.cpp \
    ModifyVocab/readervocab.cpp \
    removeword.cpp \
    widgetdisplayvocab.cpp \
    widgetmainwindow.cpp \
    widgetnewvocab.cpp \
    widgetnewvocabfirststep.cpp \
    widgetnewvocablaststep.cpp \
    widgetnewvocabsecondstep.cpp \
    widgetquizvocab.cpp \
    widgetquizvocabinitstep.cpp \
    widgetquizvocablaststep.cpp \
    ModifyVocab/writervocab.cpp

HEADERS += \
    addword.h \
    mainwindow.h \
    modifyword.h \
    ModifyVocab/readervocab.h \
    removeword.h \
    widgetdisplayvocab.h \
    widgetmainwindow.h \
    widgetnewvocab.h \
    widgetnewvocabfirststep.h \
    widgetnewvocablaststep.h \
    widgetnewvocabsecondstep.h \
    widgetquizvocab.h \
    widgetquizvocabinitstep.h \
    widgetquizvocablaststep.h \
    ModifyVocab/writervocab.h

FORMS += \
    addword.ui \
    mainwindow.ui \
    modifyword.ui \
    removeword.ui \
    widgetdisplayvocab.ui \
    widgetmainwindow.ui \
    widgetnewvocab.ui \
    widgetnewvocabfirststep.ui \
    widgetnewvocablaststep.ui \
    widgetnewvocabsecondstep.ui \
    widgetquizvocab.ui \
    widgetquizvocabinitstep.ui \
    widgetquizvocablaststep.ui

TRANSLATIONS += \
    LearnVocab_fr_FR.ts \
    LearnVocab_en_US.ts \
    LearnVocab_jap_JAP.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourceFile.qrc

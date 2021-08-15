#include "mainwindow.h"

#include "DAO/initdao.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "LearnVocab_" + QLocale(locale).name();
        if (translator.load(QString(":/i18n/%1").arg(baseName))) {
            a.installTranslator(&translator);
            break;
        }
    }
    new InitDao();
    MainWindow w;
    w.show();
    return a.exec();
}

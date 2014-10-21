#include "qthase.h"
#include <QApplication>

#include <QLibraryInfo>
#include <QLocale>
#include <QTextCodec>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("fl3sk");
    QCoreApplication::setOrganizationDomain("https://github.com/flesniak/qthase");
    QCoreApplication::setApplicationName("Qt Hase");
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QTranslator qtTranslator;
    qtTranslator.load(QLocale::system(), "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QtHase w;
    w.show();

    return a.exec();
}

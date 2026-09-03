#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "../../locales/q3tod3_map_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setOrganizationName(PROJECT_ORGANIZATION_NAME);
    w.show();
    return a.exec();
}

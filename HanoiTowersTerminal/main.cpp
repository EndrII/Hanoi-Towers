#include "terminal.h"
#include <QCoreApplication>

#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("HanoiTowers Terminal"); // <--
    QCoreApplication::setOrganizationName("QuasarApp"); // <--
    QCoreApplication::setOrganizationDomain("https://github.com/QuasarApp"); // <--
    QCoreApplication app(argc, argv);

    Terminal terminal;
    QTimer::singleShot(0, [&terminal, argc, argv]() {
        if (!terminal.send(argc, argv)) {
            QuasarAppUtils::Params::log("command not sendet!", QuasarAppUtils::Error);
            QCoreApplication::exit(10);
        }
    });

    QTimer::singleShot(1000, []() {
        QuasarAppUtils::Params::log("response timed out!", QuasarAppUtils::Error);
        QCoreApplication::exit(20);
    });

    return app.exec();
}

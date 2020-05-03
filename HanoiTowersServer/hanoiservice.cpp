#include "hanoiserver.h"
#include "hanoiservice.h"
#include <quasarapp.h>

HanoiService::HanoiService(int argc, char *argv[]):
    Patronum::Service<QCoreApplication>(argc, argv, "HanoiService") {

}

void HanoiService::start() {
    if (!_server) {
        _server = new HanoiServer();
    }
}

void HanoiService::stop() {
    if (_server) {
        delete _server;
    }
}

void HanoiService::pause() {

}

void HanoiService::resume() {

}

void HanoiService::handleReceive(const QList<Patronum::Feature> &data) {

}

QList<Patronum::Feature> HanoiService::supportedFeatures() {

}
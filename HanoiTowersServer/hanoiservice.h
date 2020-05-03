#ifndef HANOISERVICE_H
#define HANOISERVICE_H

#include <QCoreApplication>
#include <patronum.h>

class HanoiServer;

class HanoiService : public Patronum::Service<QCoreApplication>
{
public:
    HanoiService(int argc, char *argv[]);

    // QtServiceBase interface
protected:
    void start();
    void stop();
    void pause();
    void resume();

    void handleReceive(const QList<Patronum::Feature> &data);
    QList<Patronum::Feature> supportedFeatures();

private:

    HanoiServer *_server = nullptr;

};

#endif // HANOISERVICE_H
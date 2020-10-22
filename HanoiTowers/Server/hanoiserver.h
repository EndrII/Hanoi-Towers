#ifndef SNAKESERVER_H
#define SNAKESERVER_H

#define DEFAULT_ADDRESS ""
#define DEFAULT_HANOI_PORT 7770

#include <quasarapp.h>
#include <ratingusernode.h>

class HanoiServer: public NP::RatingUserNode
{
    Q_OBJECT
public:
    HanoiServer();

    QVariantMap defaultDbParams() const override;
};

#endif // SNAKESERVER_H
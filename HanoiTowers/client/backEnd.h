/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef SAVER_H
#define SAVER_H
#include "gamestate.h"
#include "hanoiclient.h"
#include "profiledata.h"
#include "settingsdata.h"
#include <quasarapp.h>
#include <QObject>
#include <QFile>
//#include <listviewmodel.h>

#define SAVE "data"

#define MAIN_FOLDER                 QDir::homePath() + "/.HanoiTowers"
#define MAIN_FOLDER_KEY             "HanoiTowersFolder"
#define MAIN_SETINGS_FILE           MAIN_FOLDER + "/" + SAVE

namespace LoginView {
class LVMainModel;
class UserData;
}
class QQmlApplicationEngine;
class RecordListModel;

class BackEnd: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool randomColor READ randomColor WRITE setRandomColor NOTIFY randomColorChanged)
    Q_PROPERTY(bool animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(bool fog READ fog WRITE setFog NOTIFY fogChanged)
    Q_PROPERTY(bool fogAnimation READ fogAnimation WRITE setFogAnimation NOTIFY fogAnimationChanged)

    Q_PROPERTY(QObject* gameState READ gameState)
    Q_PROPERTY(QObject* client READ client)
    Q_PROPERTY(QObject* profileObject READ profileObject NOTIFY profileChanged)

    Q_PROPERTY(QObject* profileList READ profileList  NOTIFY profileListChanged)
    Q_PROPERTY(QString profile READ profile WRITE setProfile NOTIFY profileChanged)



public:
    BackEnd(QQmlApplicationEngine *engine);
    ~BackEnd();

    Q_INVOKABLE QString profile() const;
    Q_INVOKABLE QObject* profileList();

    Q_INVOKABLE bool createProfile(const QString &userId, const QString& userName);

    /**
     * @brief isFirst
     * @return true if is first start
     */
    Q_INVOKABLE bool isFirst()const;

    /**
     * @brief setShowHelp set new state for show help message
     * @param state - a new state of show help message
     */
    Q_INVOKABLE void setShowHelp(bool state);

    bool fog() const;

    bool fogAnimation() const;

public slots:

    /**
     * @brief getMinSteps
     * @param lvl
     * @return minimum step of current lvl
     */
    unsigned short getMinSteps(const unsigned short lvl) const;



    /**
     * @brief reset all config to default values.
     */
    void reset();

    /**
     * @brief randomColor
     * @return return true if enable random color of plate;
     */
    bool randomColor()const;

    /**
     * @brief animation
     * @return name of render animation;
     */
    bool animation() const;

    /**
     * @brief setAnimation
     * @param name of new animation;
     */
    void setAnimation(bool valeu);

    /**
     * @brief setRandomColor
     * enabfle or disable random colors.
     */
    void setRandomColor(bool );

    /**
     * @brief gameState
     * @return
     */
    QObject *gameState();

    /**
     * @brief client
     * @return
     */
    QObject *client();

    /**
     * @brief profileObject
     * @return
     */
    QObject* profileObject() const;

    void removeUser(const QByteArray &userId);
    void setProfile(QString userId);
    void setReward(int);
    void setFog(bool fog);
    void setFogAnimation(bool fogAnimation);

signals:
    void animationChanged();
    void randomColorChanged();
    void profileListChanged();
    void profileChanged(QString profile);

    void usersListModelChanged(QObject* usersListModel);
    void showOnlinePage();


    void fogChanged(bool fog);

    void fogAnimationChanged(bool fogAnimation);

private slots:
    void handleOnlineRequestfromProfile(const QString&);
    void handleOnlineRequest(const LoginView::UserData&);
    void handleOnlineRequestError(const QString&Errr);

    void handleLogined(unsigned char);
private:
    void init();
    ProfileData *initProfile(const QByteArray &userId, const QString& userName = "");

    QuasarAppUtils::Settings *_settings = nullptr;
    LoginView::LVMainModel *_loginModel = nullptr;
    RecordListModel * _recordsTable = nullptr;

    ProfileData *_profile = nullptr;
    HanoiClient _client;

    SettingsData _settingsData;

};

#endif // SAVER_H

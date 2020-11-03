//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import NotifyModule 1.0
import "./base" as Base
import "./menu" as Menu

import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    id: gameWindow
    width: 640
    height: 480
    title: qsTr("Hanoi Towers")

    Base.Theme{
        id: theme;
    }

    header: Menu.ToolBarPage {
        state: stackview.state

        onReturnToMenu: {
            stackview.state = "MainMenu"
        }
    }

    contentData: SwipeView {
        id: stackview
        state: "MainMenu"
        anchors.fill: parent
        interactive: false
        Menu.MainMenu {
            id: mainmenu
            onStart: {
                gamePage.start();
                stackview.state = "Game"

            }
            onLoad: {
                gamePage.load();
                stackview.state = "Game"


            }
            onNewState: {
                stackview.state = state;
            }
        }

        Menu.UsersTable {
            id: usersTable
        }

        Menu.Config {
            id: configPage
        }

        About {
            id: aboutPage
        }

        Game {
            id: gamePage
        }

        states: [
            State {
                name: "MainMenu"
                PropertyChanges {
                    target: stackview
                    currentIndex: 0
                }
            },
            State {
                name: "UsersTable"
                PropertyChanges {
                    target: stackview
                    currentIndex: 1
                }
            },

            State {
                name: "Settings"
                PropertyChanges {
                    target: stackview
                    currentIndex: 2
                }
            },

            State {
                name: "About"
                PropertyChanges {
                    target: stackview
                    currentIndex: 3
                }
            },

            State {
                name: "Game"
                PropertyChanges {
                    target: stackview
                    currentIndex: 4
                }
            }
        ]
    }

    NotificationServiceView {
        anchors.fill: parent;
    }
}

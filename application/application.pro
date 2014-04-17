TEMPLATE = app
TARGET = multimote

QT += script xml

HEADERS += $$files(src/base/*.h) \
    $$files(src/prototypes/*.h)
SOURCES += $$files(src/base/*.cpp) \
    $$files(src/prototypes/*.cpp)

DEFINES += HTTP_PROTOCOL

maemo5 {
    QT += maemo5 dbus
    HEADERS += $$files(src/maemo5/*.h) \
        $$files(src/maemo5/controls/*.h)
    SOURCES += $$files(src/maemo5/*.cpp) \
        $$files(src/maemo5/controls/*.cpp)

    desktop.files = desktop/maemo5/multimote.desktop
    desktop.path = /usr/share/applications/hildon

    icon.files = desktop/maemo5/64x64/multimote.png
    icon.path = /usr/share/icons/hicolor/64x64/apps

    INSTALLS += desktop icon

} else:contains(MEEGO_EDITION,harmattan) {
    QT += declarative opengl dbus
    CONFIG += qdeclarative-boostable
    HEADERS += $$files(src/harmattan/*.h) \
        $$files(src/harmattan/controls/*.h)
    SOURCES += $$files(src/harmattan/*.cpp) \
        $$files(src/harmattan/controls/*.cpp)
    RESOURCES += src/harmattan/resources.qrc

    OTHER_FILES += $$files(src/harmattan/*.qml) \
        $$files(src/harmattan/controls/*.qml)

    desktop.files = desktop/harmattan/multimote.desktop
    desktop.path = /usr/share/applications

    icon.files = desktop/harmattan/80x80/multimote.png
    icon.path = /usr/share/icons/hicolor/80x80/apps

    INSTALLS += desktop icon
}

contains(DEFINES,BT_PROTOCOL) {
    maemo5 {
        CONFIG += mobility12
    } else {
        CONFIG += mobility
    }

    MOBILITY += connectivity
    HEADERS += $$files(src/protocols/bluetooth/*.h)
    SOURCES += $$files(src/protocols/bluetooth/*.cpp)
}

contains(DEFINES,HTTP_PROTOCOL) {
    QT += network
    HEADERS += $$files(src/protocols/http/*.h)
    SOURCES += $$files(src/protocols/http/*.cpp)
}

contains(DEFINES,IR_PROTOCOL) {
    HEADERS += $$files(src/protocols/infrared/*.h)
    SOURCES += $$files(src/protocols/infrared/*.cpp)
}

unix {
    target.path = /opt/multimote/bin
}

INSTALLS += target

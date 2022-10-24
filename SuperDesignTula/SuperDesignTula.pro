QT += quick sql multimedia multimediawidgets websockets \
    widgets
QT += network core

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../SuperServer/achivement.cpp \
        ../SuperServer/farmer.cpp \
        ../SuperServer/farmerplant.cpp \
        ../SuperServer/farmertask.cpp \
        ../SuperServer/instruments.cpp \
        ../SuperServer/logplant.cpp \
        ../SuperServer/mediaplant.cpp \
        ../SuperServer/plant.cpp \
        ../tula_hack/Client/clientgeneral.cpp \
        ../tula_hack/protocolcommunication.cpp \
        dataleft.cpp \
        main.cpp \
        plantid_api.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../SuperServer/achivement.h \
    ../SuperServer/farmer.h \
    ../SuperServer/farmerplant.h \
    ../SuperServer/farmertask.h \
    ../SuperServer/instruments.h \
    ../SuperServer/logplant.h \
    ../SuperServer/mediaplant.h \
    ../SuperServer/plant.h \
    ../tula_hack/Client/clientgeneral.h \
    ../tula_hack/protocolcommunication.h \
    dataleft.h \
    plantid_api.h

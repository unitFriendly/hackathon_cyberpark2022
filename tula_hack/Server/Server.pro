QT -= gui
 QT += websockets sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../SuperServer/achivement.cpp \
        ../../SuperServer/farmer.cpp \
        ../../SuperServer/farmerplant.cpp \
        ../../SuperServer/farmertask.cpp \
        ../../SuperServer/instruments.cpp \
        ../../SuperServer/logplant.cpp \
        ../../SuperServer/mediaplant.cpp \
        ../../SuperServer/plant.cpp \
        ../../SuperServer/servercontroller.cpp \
        ../commondata.cpp \
        ../protocolcommunication.cpp \
        main.cpp \
        servergeneral.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../SuperServer/achivement.h \
    ../../SuperServer/farmer.h \
    ../../SuperServer/farmerplant.h \
    ../../SuperServer/farmertask.h \
    ../../SuperServer/instruments.h \
    ../../SuperServer/logplant.h \
    ../../SuperServer/mediaplant.h \
    ../../SuperServer/plant.h \
    ../../SuperServer/servercontroller.h \
    ../commondata.h \
    ../protocolcommunication.h \
    servergeneral.h

RESOURCES += resourcesServer.qrc

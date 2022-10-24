QT -= gui

QT += network sql
CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        achivement.cpp \
        farmer.cpp \
        farmerplant.cpp \
        farmertask.cpp \
        instruments.cpp \
        logplant.cpp \
        main.cpp \
        mediaplant.cpp \
        plant.cpp \
        servercontroller.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    achivement.h \
    farmer.h \
    farmerplant.h \
    farmertask.h \
    instruments.h \
    logplant.h \
    mediaplant.h \
    plant.h \
    servercontroller.h

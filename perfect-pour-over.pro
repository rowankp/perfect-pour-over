QT  += core
QT  += gui
QT  += charts
QT  += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    charts/livechart.cpp \
    charts/phchart.cpp \
    charts/temperaturechart.cpp \
    components/averagesview.cpp \
    components/brewtimer.cpp \
    components/glossarywidget.cpp \
    components/individualview.cpp \
    components/newbrewwidget.cpp \
    components/roastslider.cpp \
    components/tastingwheelwidget.cpp \
    components/viewbrewswidget.cpp \
    database/databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    simulation/dummydata.cpp

HEADERS += \
    brewdatastructure.h \
    charts/livechart.h \
    charts/phchart.h \
    charts/temperaturechart.h \
    components/averagesview.h \
    components/brewtimer.h \
    components/glossarywidget.h \
    components/individualview.h \
    components/newbrewwidget.h \
    components/roastslider.h \
    components/tastingwheelwidget.h \
    components/viewbrewswidget.h \
    database/databasemanager.h \
    mainwindow.h \
    simulation/dummydata.h

FORMS += \
    components/averagesview.ui \
    components/glossarywidget.ui \
    components/individualview.ui \
    components/newbrewwidget.ui \
    components/tastingwheelwidget.ui \
    components/viewbrewswidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    database/BrewData.db \
    database/create-tables.sql \
    references/flavor-wheel.PNG \
    references/logo.png


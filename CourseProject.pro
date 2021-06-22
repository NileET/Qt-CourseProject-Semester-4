QT       += core gui \
            charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutprogramm.cpp \
    checkboxdelegate.cpp \
    device.cpp \
    graphics.cpp \
    main.cpp \
    mainwindow.cpp \
    proxymodel.cpp \
    spinboxdelegate.cpp \
    switch.cpp \
    tablemodel.cpp \
    tableview.cpp

HEADERS += \
    aboutprogramm.hpp \
    checkboxdelegate.hpp \
    device.hpp \
    graphics.hpp \
    mainwindow.hpp \
    proxymodel.hpp \
    spinboxdelegate.hpp \
    switch.hpp \
    tablemodel.hpp \
    tableview.hpp

FORMS += \
    aboutprogramm.ui \
    graphics.ui \
    mainwindow.ui

TRANSLATIONS += \
    translations/CourseProject_ru_RU.ts \
    translations/CourseProject_en_US.ts \
    translations/CourseProject_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ico.qrc

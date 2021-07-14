QT       += core gui\
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfeaturedialog.cpp \
    blacklistValidator.cpp \
    comboboxdelegate.cpp \
    dbInterface.cpp \
    filewidget.cpp \
    filewidgetdelegate.cpp \
    insertDialog.cpp \
    main.cpp \
    recordModel.cpp \
    sectionsModel.cpp \
    test.cpp \
    vcs_tool.cpp

HEADERS += \
    addfeaturedialog.h \
    blacklistValidator.h \
    comboboxdelegate.h \
    dbInterface.h \
    filewidget.h \
    filewidgetdelegate.h \
    insertDialog.h \
    recordModel.h \
    sectionsModel.h \
    test.h \
    vcs_tool.h

FORMS += \
    addfeaturedialog.ui \
    vcs_tool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

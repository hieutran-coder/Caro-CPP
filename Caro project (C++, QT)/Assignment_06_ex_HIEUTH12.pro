QT += quick

SOURCES += \
        bot.cpp \
        carocontroller.cpp \
        main.cpp

resources.files = with_human.qml
resources.files += with_bot.qml
resources.files += main.qml
resources.files += win.qml
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    guide.qml \
    win.qml \
    with_bot.qml \
    with_human.qml

HEADERS += \
    bot.h \
    carocontroller.h

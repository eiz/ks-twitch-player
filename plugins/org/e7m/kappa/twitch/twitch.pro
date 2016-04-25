TEMPLATE = lib
TARGET = org-e7m-kappa-twitch
QT += qml quick
CONFIG += qt plugin marvell debug c++11

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_LFLAGS += '-Wl,-rpath,\'/home/steam/lib\''

TARGET = $$qtLibraryTarget($$TARGET)
uri = org.e7m.kappa.twitch

# Input
SOURCES += \
    plugin.cpp \
    twitchapiclient.cpp

HEADERS += \
    plugin.h \
    twitchapiclient.h

OTHER_FILES = qmldir \
    plugin.json \
    Menu.qml \
    Home.qml \
    kappa.json

LIBS += -lssl -lcrypto

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = $$OTHER_FILES

unix {
    installPath = /kappa/plugins/org/e7m/kappa/twitch
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

marvell {
        INCLUDEPATH += \
                $(MARVELL_ROOTFS)/usr/include/SDL2 \
}

removesteamlink.commands = $(RM) -r steamlink
distclean.depends = removesteamlink
QMAKE_EXTRA_TARGETS += distclean removesteamlink

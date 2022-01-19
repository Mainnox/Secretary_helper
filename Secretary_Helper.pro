QT       += core gui widgets
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acomptedialog.cpp \
    bilandialog.cpp \
    dialog.cpp \
    finddialog.cpp \
    formfacnoimagedialog.cpp \
    formheaderdialog.cpp \
    formtotaldialog.cpp \
    formularedialog.cpp \
    informationdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    nouvelleimagedialog.cpp \
    nouvellelignedialog.cpp \
    paydialog.cpp \
    printdialog.cpp \
    recapdialog.cpp \
    titredialog.cpp

HEADERS += \
    acomptedialog.h \
    bilandialog.h \
    dialog.h \
    finddialog.h \
    formfacnoimagedialog.h \
    formheaderdialog.h \
    formtotaldialog.h \
    formularedialog.h \
    informationdialog.h \
    mainwindow.h \
    nouvelleimagedialog.h \
    nouvellelignedialog.h \
    paydialog.h \
    printdialog.h \
    recapdialog.h \
    titredialog.h

FORMS += \
    acomptedialog.ui \
    bilandialog.ui \
    dialog.ui \
    finddialog.ui \
    formfacnoimagedialog.ui \
    formheaderdialog.ui \
    formtotaldialog.ui \
    formularedialog.ui \
    informationdialog.ui \
    mainwindow.ui \
    nouvelleimagedialog.ui \
    nouvellelignedialog.ui \
    paydialog.ui \
    printdialog.ui \
    recapdialog.ui \
    titredialog.ui

TRANSLATIONS += \
    Secretary_Helper_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

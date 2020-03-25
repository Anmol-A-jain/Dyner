
QT       += core gui network sql xml serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    data/allaction.cpp \
    dyner.cpp \
    main.cpp \
    data/databasecon.cpp \
    data/globaldata.cpp \
    data/xmlmanipulation.cpp \
    menu/ServerManagement/servermanagement.cpp \
    menu/admin/adminwidget.cpp \
    menu/admin/customWidget/itemwidget.cpp \
    menu/admin/DialogBox/additem.cpp \
    menu/admin/DialogBox/editcategory.cpp \
    menu/admin/DialogBox/edititem.cpp \
    menu/admin/DialogBox/edittablenoanddiscount.cpp \
    menu/bill_history/billhistorywidget.cpp \
    menu/bill_history/customWidget/history.cpp \
    menu/menu_buttons/menubuttons.cpp \
    menu/order/DialogBox/statusdialogbox.cpp \
    menu/order/customWidget/displaywidget.cpp \
    menu/order/customWidget/nestedCustomWidget/statusorderitem.cpp \
    menu/order/customWidget/orderdatawidget.cpp \
    menu/order/customWidget/orderitemdata.cpp \
    menu/order/DialogBox/addorderitem.cpp \
    menu/order/orderwidget.cpp \
    menu/order/DialogBox/paymentmathod.cpp \
    server/dynerserver.cpp \
    server/mytcpsocket.cpp \
    menu/ServerManagement/customWidget/waiterinformation.cpp


HEADERS += \
    data/allaction.h \
    dyner.h \
    data/databasecon.h \
    data/globaldata.h \
    data/xmlmanipulation.h \
    menu/ServerManagement/servermanagement.h \
    menu/admin/adminwidget.h \
    menu/admin/customWidget/itemwidget.h \
    menu/admin/DialogBox/additem.h \
    menu/admin/DialogBox/editcategory.h \
    menu/admin/DialogBox/edititem.h \
    menu/admin/DialogBox/edittablenoanddiscount.h \
    menu/bill_history/billhistorywidget.h \
    menu/bill_history/customWidget/history.h \
    menu/menu_buttons/menubuttons.h \
    menu/order/DialogBox/addorderitem.h \
    menu/order/DialogBox/statusdialogbox.h \
    menu/order/customWidget/displaywidget.h \
    menu/order/customWidget/nestedCustomWidget/statusorderitem.h \
    menu/order/customWidget/orderdatawidget.h \
    menu/order/customWidget/orderitemdata.h \
    menu/order/orderwidget.h \
    menu/order/DialogBox/paymentmathod.h \
    server/dynerserver.h \
    server/mytcpsocket.h \
    menu/ServerManagement/customWidget/waiterinformation.h

FORMS += \
    dyner.ui \
    menu/ServerManagement/servermanagement.ui \
    menu/admin/adminwidget.ui \
    menu/admin/customWidget/itemwidget.ui \
    menu/admin/DialogBox/additem.ui \
    menu/admin/DialogBox/editcategory.ui \
    menu/admin/DialogBox/edititem.ui \
    menu/admin/DialogBox/edittablenoanddiscount.ui \
    menu/bill_history/billhistorywidget.ui \
    menu/bill_history/customWidget/history.ui \
    menu/menu_buttons/menubuttons.ui \
    menu/order/DialogBox/statusdialogbox.ui \
    menu/order/customWidget/nestedCustomWidget/statusorderitem.ui \
    menu/order/customWidget/orderdatawidget.ui \
    menu/order/orderwidget.ui\
    menu/order/customWidget/displaywidget.ui \
    menu/order/customWidget/orderitemdata.ui \
    menu/order/DialogBox/addorderitem.ui \
    menu/order/DialogBox/paymentmathod.ui \
    menu/ServerManagement/customWidget/waiterinformation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = imViewer
TEMPLATE = app

CONFIG += c++17
msvc:CONFIG +=/Zc:__cplusplus

#QMAKE_CXXFLAGS += -std=c++17

TEMPLATE = app

INCLUDEPATH += ./ \
    dialog/ \
    utils/  \
    mainwindow/

HEADERS += dialog/dialog_exp_transform.h \
    HIKV.h \
    dialog/dialog_califrom3pts.h \
    dialog/dialog_linear_gray.h \
    dialog/dialog_log_grey.h    \
    dialog/dialog_power_grey.h \
    dialog/dialog_ptsnumrecord.h \
    dialog/dialog_stretch_transform.h   \
    dialog/dialog_two_threshold_transform.h \
    dialog/dlg_hkcamconnect.h \
    dialog/dlg_imagenamed.h \
    dialog/dlg_imgleap.h \
    dialog/dlg_resolutionmanager.h \
    dialog/dlg_sethkspecinfo.h \
    main.h \
    mainwindow/graphicsview.h \
    mainwindow/main.h \
    mainwindow/mainwindow.h    \
    dialog/dialog_gaussianblur.h  \
    mainwindow/mygraphicsitem.hpp \
    mainwindow/mygraphicspixmapitem.h \
    mvs/include/CameraParams.h \
    mvs/include/MvCameraControl.h \
    mvs/include/MvErrorDefine.h \
    mvs/include/MvISPErrorDefine.h \
    mvs/include/MvObsoleteInterfaces.h \
    mvs/include/MvSdkExport.h \
    mvs/include/ObsoleteCamParams.h \
    mvs/include/PixelType.h \
    t_grabimg.h \
    utils/ImageSaver.hpp \
    utils/histogram.h   \
    utils/limitedDqe.hpp \
    utils/medianfilter.h    \
    utils/modeLinePt.hpp \
    utils/tools.h   \
    utils/qcustomplot.h   \



SOURCES += dialog/dialog_exp_transform.cpp \
    HIKV.cpp \
    dialog/dialog_califrom3pts.cpp \
    dialog/dialog_gaussianblur.cpp  \
    dialog/dialog_linear_gray.cpp   \
    dialog/dialog_log_grey.cpp  \
    dialog/dialog_power_grey.cpp    \
    dialog/dialog_ptsnumrecord.cpp \
    dialog/dialog_stretch_transform.cpp \
    dialog/dialog_two_threshold_transform.cpp   \
    dialog/dlg_hkcamconnect.cpp \
    dialog/dlg_imagenamed.cpp \
    dialog/dlg_imgleap.cpp \
    dialog/dlg_resolutionmanager.cpp \
    dialog/dlg_sethkspecinfo.cpp \
    mainwindow/mainwindow.cpp  \
    mainwindow/graphicsview.cpp \
    mainwindow/mygraphicspixmapitem.cpp \
    t_grabimg.cpp \
    utils/gaussianblur.cpp  \
    utils/histogram.cpp \
    utils/medianfilter.cpp  \
    utils/qcustomplot.cpp   \
    utils/tools.cpp \
    main.cpp

FORMS    += mainwindow/mainwindow.ui \
    dialog/dialog_califrom3pts.ui \
    dialog/dialog_ptsnumrecord.ui \
    dialog/dlg_hkcamconnect.ui \
    dialog/dlg_imagenamed.ui \
    dialog/dlg_imgleap.ui \
    dialog/dlg_resolutionmanager.ui \
    dialog/dlg_sethkspecinfo.ui \
    dialog/gaussianblurdialog.ui \
    dialog/dialog_linear_gray.ui \
    dialog/dialog_log_grey.ui \
    dialog/dialog_power_grey.ui \
    dialog/dialog_exp_transform.ui \
    dialog/dialog_two_threshold_transform.ui \
    dialog/dialog_stretch_transform.ui

RESOURCES += \
    res/default.qrc

TRANSLATIONS += res/cn.ts

DISTFILES += \
#    mvs/lib/BCB_Convert_x64.bat \
    mvs/lib/MvCameraControl.lib \
    res/Line_Chart_72px.png \
    res/MdiImageMove.svg \
    res/NotoV1VideoCamera.svg \
    res/Open_folder_full_48px_1186194_easyicon.net.png \
    res/about.svg \
    res/blur_on_72px.png \
    res/brightness.svg \
    res/chinese.png \
    res/clear.svg \
    res/cn.qm \
    res/english.png \
    res/frame_1.png \
    res/frame_2.png \
    res/frame_3.png \
    res/fun_exp.png \
    res/histogram.png \
    res/horizontal.png \
    res/left.png \
    res/lineGrey.gif \
    res/line_graphic_72p.png \
    res/log.png \
    res/logo_1.png \
    res/logo_2.png \
    res/metal.png \
    res/oldtimecamera.ico \
    res/open.svg \
    res/player-pause.icon.jpg \
    res/quill_72px.png \
    res/restore.png \
    res/right.png \
    res/save.svg \
    res/stop-fill.svg \
    res/temperature_72px.png \
    res/vertical.png \
    res/zoom.png
 #    mvs/lib/libMvCameraControl.a

#MVS

win32: LIBS += -L$$PWD/mvs/lib/ -lMvCameraControl

INCLUDEPATH += $$PWD/mvs/include
DEPENDPATH += $$PWD/mvs/include

#QMAKE_CXXFLAGS += -finput-charset=UTF-8
CODECFORSRC = UTF-8
QMAKE_CXXFLAGS += -execution-charset:utf-8
QMAKE_CXXFLAGS += -source-charset:utf-8

TEMPLATE = lib
CONFIG += windows c++11 staticlib
CONFIG -= app_bundle qt

HEADERS += \
    tensor3.h \
    util.h \
    ilayer.h \
    alosslayer.h \
    tanhlayer.h \
    fullyconnectedlayer.h \
    softmaxlayer.h

SOURCES += \
    tensor3.cpp \
    util.cpp \
    ilayer.cpp \
    alosslayer.cpp \
    tanhlayer.cpp \
    fullyconnectedlayer.cpp \
    softmaxlayer.cpp

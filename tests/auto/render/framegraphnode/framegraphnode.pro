TEMPLATE = app

TARGET = tst_framegraphnode
QT += core-private 3dcore 3dcore-private 3drenderer 3drenderer-private testlib

CONFIG += testcase

SOURCES += tst_framegraphnode.cpp

include(../commons/commons.pri)

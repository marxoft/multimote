TEMPLATE = lib
TARGET = helloworld
QT += core
QT -= gui
HEADERS += helloworld.h
SOURCES += helloworld.cpp

remotepath = /home/user/MultiMote/remotes/HelloWorld

target.path = "$$remotepath"
remote.files = remote.xml
remote.path = "$$remotepath"

INSTALLS += target remote

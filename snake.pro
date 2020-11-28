QT += widgets

HEADERS       = \
    map.h \
    snake.h
SOURCES       = \
                main.cpp \
                map.cpp \
                snake.cpp

QMAKE_PROJECT_NAME = qt_snake

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qt_snake
INSTALLS += target

FORMS += \
    map.ui

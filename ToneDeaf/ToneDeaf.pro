#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T22:32:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToneDeaf
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../include/Box2D/Collision/Shapes/b2ChainShape.cpp \
    ../include/Box2D/Collision/Shapes/b2CircleShape.cpp \
    ../include/Box2D/Collision/Shapes/b2EdgeShape.cpp \
    ../include/Box2D/Collision/Shapes/b2PolygonShape.cpp \
    ../include/Box2D/Collision/b2BroadPhase.cpp \
    ../include/Box2D/Collision/b2CollideCircle.cpp \
    ../include/Box2D/Collision/b2CollideEdge.cpp \
    ../include/Box2D/Collision/b2CollidePolygon.cpp \
    ../include/Box2D/Collision/b2Collision.cpp \
    ../include/Box2D/Collision/b2Distance.cpp \
    ../include/Box2D/Collision/b2DynamicTree.cpp \
    ../include/Box2D/Collision/b2TimeOfImpact.cpp \
    ../include/Box2D/Common/b2BlockAllocator.cpp \
    ../include/Box2D/Common/b2Draw.cpp \
    ../include/Box2D/Common/b2Math.cpp \
    ../include/Box2D/Common/b2Settings.cpp \
    ../include/Box2D/Common/b2StackAllocator.cpp \
    ../include/Box2D/Common/b2Timer.cpp \
    ../include/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    ../include/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    ../include/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
    ../include/Box2D/Dynamics/Contacts/b2Contact.cpp \
    ../include/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
    ../include/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    ../include/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    ../include/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    ../include/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
    ../include/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2GearJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2Joint.cpp \
    ../include/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
    ../include/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
    ../include/Box2D/Dynamics/b2Body.cpp \
    ../include/Box2D/Dynamics/b2ContactManager.cpp \
    ../include/Box2D/Dynamics/b2Fixture.cpp \
    ../include/Box2D/Dynamics/b2Island.cpp \
    ../include/Box2D/Dynamics/b2World.cpp \
    ../include/Box2D/Dynamics/b2WorldCallbacks.cpp \
    ../include/Box2D/Rope/b2Rope.cpp \
    mycanvas.cpp \
    qsfmlcanvas.cpp \
    shape.cpp \
    ../include/MIDITool/CraigsAppSrc/Binasc.cpp \
    ../include/MIDITool/CraigsAppSrc/MidiEvent.cpp \
    ../include/MIDITool/CraigsAppSrc/MidiEventList.cpp \
    ../include/MIDITool/CraigsAppSrc/MidiFile.cpp \
    ../include/MIDITool/CraigsAppSrc/MidiMessage.cpp \
    ../include/MIDITool/CraigsAppSrc/Options.cpp \
    ../include/MIDITool/MidiPlayingSrc/QMidiFile.cpp \
    ../include/MIDITool/MidiPlayingSrc/QMidiOut.cpp \
    ../include/MIDITool/miditool.cpp \
    spritesheet.cpp \
    shapecontainer.cpp \
    congratsdialog.cpp \
    expanddialog.cpp

HEADERS += \
        mainwindow.h \
    mycanvas.h \
    qsfmlcanvas.h \
    shape.h \
    ../include/MIDITool/CraigsAppSrc/Binasc.h \
    ../include/MIDITool/CraigsAppSrc/MidiEvent.h \
    ../include/MIDITool/CraigsAppSrc/MidiEventList.h \
    ../include/MIDITool/CraigsAppSrc/MidiFile.h \
    ../include/MIDITool/CraigsAppSrc/MidiMessage.h \
    ../include/MIDITool/CraigsAppSrc/Options.h \
    ../include/MIDITool/MidiPlayingSrc/QMidiFile.h \
    ../include/MIDITool/MidiPlayingSrc/QMidiOut.h \
    ../include/MIDITool/miditool.h \
    spritesheet.h \
    shapecontainer.h \
    congratsdialog.h \
    expanddialog.h

FORMS += \
        mainwindow.ui \
    congratsdialog.ui \
    expanddialog.ui

INCLUDEPATH += ../include
DEPENDPATH += ../include

LIBS += -L../libs/
LIBS += -L../bin/

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-window-d -lsfml-system-d -lsfml-network-d -lsfml-main-d -lsfml-graphics-d

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-window -lsfml-system -lsfml-network -lsfml-main -lsfml-graphics

 ## This is used by the MIDI playback library, to ensure the correct system is used on each OS.
win32 {
        LIBS += -lwinmm
        SOURCES += ../include/MIDITool/MidiPlayingSrc/OS/QMidi_Win32.cpp
}

linux* {
        LIBS += -lasound
        SOURCES += ../include/MIDITool/MidiPlayingSrc/OS/QMidi_ALSA.cpp
}

haiku* {
        LIBS += -lmidi2
        SOURCES += ../include/MIDITool/MidiPlayingSrc/OS/QMidi_Haiku.cpp
}

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../LessonPDF/Lesson 0.png \
    ../LessonPDF/Lesson 1.png \
    ../LessonPDF/Lesson 2.png \
    ../LessonPDF/Lesson 3.png \
    ../LessonPDF/Lesson 4.png \
    ../LessonPDF/Lesson 5.png \
    ../LessonPDF/Lesson 6.png

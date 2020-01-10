#include "MIDITool/miditool.h"
#include <QElapsedTimer>

MidiTool::MidiTool() :
    fileLoaded(false)
{
    midi_out.connect(0);
    midi_out.setInstrument(0, 0);
}

bool MidiTool::openFile(std::string filePath)
{
    file.read(filePath);

    if (!file.status())
    {
        return false;
    }

    fileLoaded = true;
    passedEOF = false;
    file.absoluteTicks();
    file.sortTracks();
    file.joinTracks();
    file.doTimeAnalysis();
    eventList = file[0];
    eventList.linkNotePairs();

    currentEventPos = 0;

    for (; currentEventPos < eventList.getSize(); currentEventPos++)
    {
        MidiEvent currEvent = eventList[currentEventPos];

        if (currEvent.isTempo())
        {
            tempoEvent = currentEventPos;
            return true;
        }
        else
        {
            continue;
        }
    }

    return false;
}

bool MidiTool::getNextNote()
{
    if (!fileLoaded)
    {
        return false;
    }

    currentEventPos++;
    for (; currentEventPos < eventList.getSize(); currentEventPos++)
    {
        MidiEvent currEvent = eventList[currentEventPos];

        if (currEvent.isTempo())
        {
            tempoEvent = currentEventPos;
            continue;
        }
        else if (currEvent.isNoteOn())
        {
            currentNote = currentEventPos;
            return true;
        }
        else
        {
            continue;
        }
    }

    passedEOF = true;
    return false;
}

int MidiTool::getNote()
{
    if (!fileLoaded || !eventList[currentNote].isNoteOn())
    {
        return -1;
    }

    return (int)eventList[currentNote][1];
}

std::string MidiTool::getNoteAsString()
{
    if (!fileLoaded || !eventList[currentNote].isNoteOn())
    {
        return "";
    }

    return notes[getNote()];
}

int MidiTool::getNoteVelocity()
{
    if (!fileLoaded || !eventList[currentNote].isNoteOn())
    {
        return -1;
    }

    return (int)eventList[currentNote][2];
}

double MidiTool::getNoteLength()
{
    if (!fileLoaded || !eventList[currentNote].isNoteOn())
    {
        return -1.0;
    }

    return eventList[currentNote].getDurationInSeconds();
}

double MidiTool::getNoteStart()
{
    if (!fileLoaded || !eventList[currentNote].isNoteOn())
    {
        return -1.0;
    }

    return file.getTimeInSeconds(0, currentNote);
}

double MidiTool::getNoteEnd()
{
    if (!fileLoaded || !eventList[currentNote].isNoteOn())
    {
        return -1.0;
    }

    return getNoteStart() + getNoteLength();
}

double MidiTool::getFileTempoInSeconds()
{
    if (!fileLoaded)
    {
        return -1.0;
    }

    return eventList[tempoEvent].getTempoSeconds();
}

double MidiTool::getFileTempoInMicroSeconds()
{
    if (!fileLoaded)
    {
        return -1.0;
    }

    return eventList[tempoEvent].getTempoMicroseconds();
}

double MidiTool::getFileTempoInBPM()
{
    if (!fileLoaded)
    {
        return -1.0;
    }

    return eventList[tempoEvent].getTempoBPM();
}

double MidiTool::getQuarterNoteLengthInSeconds()
{
    if (!fileLoaded)
    {
        return -1.0;
    }

    return 60 / getFileTempoInBPM();
}

int MidiTool::getQuarterNoteLengthInTicks()
{
    if (!fileLoaded)
    {
        return -1.0;
    }

    return file.getTicksPerQuarterNote();
}

bool MidiTool::EOFPassed()
{
    return passedEOF;
}

void MidiTool::playCurrentNote()
{
    if (!fileLoaded || !eventList[currentNote].isNoteOn())
    {
        return;
    }

    double length = getNoteLength() * 1000;
    int noteVal = getNote();
    midi_out.setInstrument(0, 0);
    midi_out.noteOn(noteVal, 0, getNoteVelocity());
    QTimer::singleShot((int) (length + 0.5), [this, noteVal](){noteStop(noteVal);});
}

void MidiTool::playNote(int noteVal, int length, int instrument = 0, int velocity = 64)
{
    midi_out.setInstrument(0, instrument);
    midi_out.noteOn(noteVal, 0, velocity);
    QTimer::singleShot(length, [this, noteVal](){noteStop(noteVal);});
}

void MidiTool::noteStart(int noteVal)
{
    if (timer.isValid())
    {
        //starts a second elapsedTimer if there is another note pressed
        //this is so it can handle multiple note presses
        timer2.start();
    }
    else
        timer.start(); //starts elapsedTimer to measure how long note is pressed
    midi_out.noteOn(noteVal, 0, 64);
}

int MidiTool::noteStop(int noteVal)
{
    int timeElapsed;
    midi_out.noteOff(noteVal, 0);
    if (timer2.isValid())
    {
        timeElapsed = timer2.elapsed(); //returns how long the note has been held
        timer2.invalidate();
        return timeElapsed;
    }
    else
    {
        timeElapsed = timer.elapsed();
        timer.invalidate();
        return timeElapsed;
    }
}

void MidiTool::changeInstrument(int instrument)
{
    midi_out.setInstrument(0, instrument);
}

MidiTool::~MidiTool()
{

}

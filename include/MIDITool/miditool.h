/*
    Author: Vladimir Srdic
    Class: CS3505
    Assignment: A8
    Credits: - Github user craigsapp for his "midifile" library that is used
                here to read and parse Midi files.
             - Github user waddlesplash (and contributors) for his "QMidi" library
                that is used here for playing Midi sounds (as well as for making it
                easy to use with Qt).

    Class purpose: This "MidiTool" class is a facade for the afformentioned libraries
                    that merges the two into one easy to use Midi parser and Midi player.
                    it contains an assortment of methods to pull from each note event in a midi
                    file, as well as tempo and other file specific settings.
*/

#ifndef MIDITOOL_H
#define MIDITOOL_H

#include <QString>
#include <QTimer>
#include <QElapsedTimer>

#include <MIDITool/MidiPlayingSrc/QMidiOut.h>
#include <MIDITool/CraigsAppSrc/MidiFile.h>
#include <MIDITool/CraigsAppSrc/MidiEvent.h>
#include <MIDITool/CraigsAppSrc/MidiEventList.h>

class MidiTool
{
public:
    // Default constructor, connects the midi_out object to the top most midi
    // device on the computer this program is run on.
    // TODO: Find out how to get default midi source.
    MidiTool();

    // Destructor, largely not used.
    ~MidiTool();

    // Attempts to open the file at the given path. Returns true if the file is successfully opened and
    // there is a tempo event in the file, false otherwise.
    //
    // This method will also do a few pre-note parsing methods, such as merging the tracks for easier
    // parsing and applying a few settings. This file will also search for the first tempo event
    // in the midi file, to set the tempo variables.
    // This method WILL NOT find the first note in the midi, so getNextNote should always be called before
    // retrieving information about a note.
    bool openFile(std::string filePath);

    // Attempts to retrieve the next ON note in the Midi file. Returns true if this is successfull, false
    // otherwise. If a note is not retrieved, we have reached end of file and the passedEOF param is set
    // to true.
    //
    // This method should always be called before retrieving note information, after opening the file.
    //
    // This method will return false if a file has not been opened yet.
    bool getNextNote();

    // Returns the Midi numerical representation of the currently found note. This number is an int between
    // 0 and 127, dictating the pitch and style of the note.
    // Returns -1 if a file has not been opened yet, or getNextNote has not been called yet.
    int getNote();

    // Returns the current note as a string formatted as such: 'X Y' where X is the note's name (i.e. C# or B)
    // and Y is the octave of the note, ranging from 0 to 11.
    // Returns "" if a file has not been opened yet.
    std::string getNoteAsString();

    // Returns the velocity of the current note event. This generally dictates the volume of a note, and is
    // defaulted to 64 in most cases (ranges from 0 to 127).
    // Returns -1 if a file has not been opened yet, or getNextNote has not been called yet.
    int getNoteVelocity();

    // Returns the amount of time the current note should be played for, in seconds.
    // Returns -1 if a file has not been opened yet, or getNextNote has not been called yet.
    double getNoteLength();

    // Returns the absolute start time of the current note, in reference to the beginning of
    // the midi file, in seconds.
    //
    // For example, if your current note is the second note in the midi file, and the previous was
    // a quarter note of length .6 seconds, the current notes starting time would be .6
    // Returns -1 if a file has not been opened yet, or getNextNote has not been called yet.
    double getNoteStart();

    // Returns the absolute end time of the current note, in reference to the beginning of
    // the midi file, in seconds.
    // Returns -1 if a file has not been opened yet, or getNextNote has not been called yet.
    double getNoteEnd();

    // Returns the tempo of the opened file in seconds.
    // Returns -1 if a file has not been opened yet.
    double getFileTempoInSeconds();

    // Returns the tempo of the opened file in MICROseconds.
    // Returns -1 if a file has not been opened yet.
    double getFileTempoInMicroSeconds();

    // Returns the tempo of the opened file in Beats Per Minute
    // Returns -1 if a file has not been opened yet.
    double getFileTempoInBPM();

    // Returns the length of a quarter note in the opened file in seconds.
    // Returns -1 if a file has not been opened yet.
    double getQuarterNoteLengthInSeconds();

    // Returns the length of a quarter note in the opened file in MIDI ticks.
    // Returns -1 if a file has not been opened yet.
    int getQuarterNoteLengthInTicks();

    // Plays the currently active note.
    // If called after reachign the end of the file, it will play the last note in the file.
    // Nothing will occur if a file has not been opened yet, or if a note has not been retrieved yet.
    void playCurrentNote();

    // Plays a note with the given note value (MIDI format), for the given length (in milliseconds),
    // with the given instrument, with the given velocity.
    // instrument is defaulted to 0 (grand acoustic piano) and velocity is defaulted to 64.
    // Params: noteVal, length, instrument, velocity
    void playNote(int, int, int, int);

    // Returns whether the user has passed the end of the opened midi file's notes.
    // Should be used liberally when iterating through file notes.
    bool EOFPassed();

    // Used to start playing a note
    void noteStart(int);

    // Used to stop a note that is played, after the desired length has expired.
    int noteStop(int);

    // Used to change the instrument current being played back
    void changeInstrument(int);

private slots:

private:
    // MidiFile back that is used for parsing/reading the given file.
    MidiFile file;

    // List of Events in the opened midi file.
    MidiEventList eventList;

    // Index that dictates which event is currently hovered in the eventList.
    int currentEventPos;

    // index of current note in eventList.
    int currentNote;

    // index of the most recent tempoEvent in eventList.
    int tempoEvent;

    // QMidiOut back that handles playback of midi notes.
    QMidiOut midi_out;

    // Dictates whether the user has passed the end of the notes in eventList.
    bool passedEOF;

    // Dictates whether a file has been loaded with this MidiTool.
    bool fileLoaded;

    // Both used to calculate time between a button press and release
    QElapsedTimer timer;
    QElapsedTimer timer2;


    // Array of notes used to find the human-language equivalent of a MIDI note.
    std::string notes [128] = {"C 1", "C# 1", "D 1", "D# 1", "E 1", "F 1", "F# 1", "G 1", "G# 1", "A 1", "A# 1", "B 1",
                            "C 2", "C# 2", "D 2", "D# 2", "E 2", "F 2", "F# 2", "G 2", "G# 2", "A 2", "A# 2", "B 2",
                            "C 3", "C# 3", "D 3", "D# 3", "E 3", "F 3", "F# 3", "G 3", "G# 3", "A 3", "A# 3", "B 3",
                            "C 4", "C# 4", "D 4", "D# 4", "E 4", "F 4", "F# 4", "G 4", "G# 4", "A 4", "A# 4", "B 4",
                            "C 5", "C# 5", "D 5", "D# 5", "E 5", "F 5", "F# 5", "G 5", "G# 5", "A 5", "A# 5", "B 5",
                            "C 6", "C# 6", "D 6", "D# 6", "E 6", "F 6", "F# 6", "G 6", "G# 6", "A 6", "A# 6", "B 6",
                            "C 7", "C# 7", "D 7", "D# 7", "E 7", "F 7", "F# 7", "G 7", "G# 7", "A 7", "A# 7", "B 7",
                            "C 8", "C# 8", "D 8", "D# 8", "E 8", "F 8", "F# 8", "G 8", "G# 8", "A 8", "A# 8", "B 8",
                            "C 9", "C# 9", "D 9", "D# 9", "E 9", "F 9", "F# 9", "G 9", "G# 9", "A 9", "A# 9", "B 9",
                            "C 10", "C# 10", "D 10", "D# 10", "E 10", "F 10", "F# 10", "G 10", "G# 10", "A 10", "A# 10", "B 10",
                            "C 11", "C# 11", "D 11", "D# 11", "E 11", "F 11", "F# 11", "G 11"};

};

#endif // MIDITOOL_H

#ifndef MYCANVAS_H
#define MYCANVAS_H
#include "qsfmlcanvas.h"
#include "spritesheet.h"
#include "shapecontainer.h"
#include "MIDITool/miditool.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <shape.h>
#include <QTimer>

class MyCanvas : public QSFMLCanvas
{
    Q_OBJECT

    // Enum for knowing what type of note to draw (Usable only after we have a sprite sheet reading library).
    enum class NoteLength
    {
        WholeNote,
        HalfNote,
        QuarterNote,
        EigthNote,
        Sharp
    };

public :
    MyCanvas(QWidget* Parent);
    ~MyCanvas();
    void OnInit();
    void OnUpdate();

private :
    b2World* world;
    QMap<int, QList<Shape>> shapes;
    QList<ShapeContainer> toCreate;
    QList<Shape> toDelete;
    QElapsedTimer timer;
    qint64 userClick = 0;
    qint64 timeMargin;
    int nextNoteIndex;
    int bpm;
    int margin;
    int currentNote;
    bool clearQueued = false;

    void drawStaff();
    int create(float x, float y, sf::Texture *tex, int key, bool sharp, int ledger);
    void createf(float x, float y);
    float getNote(int note);
    int createFromNote(int note, NoteLength noteLength, bool testPage);

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    int lNoteAmount = 0;
    int lNotesCorrect = 0;
    int lNotesPassed = 0;
    int lessonToLoad = -1;

    std::vector<float> xs;
    std::vector<float> ys;

    sf::View view;
    sf::Clock myClock;
    sf::Texture* clefTex;

    SpriteSheet* sheet;
    MidiTool midi_tool;

public slots:
    void getKeyPressed(int, bool testPage);
    void getKeyReleased(int, bool testPage);
    void createFromNoteSignal(int note, NoteLength noteLength);
    void clear();
    void queueLessonLoad(int);
    void queueNextNote();

signals:
    void sendLessonEnd(int, int);

};
#endif // MYCANVAS_H

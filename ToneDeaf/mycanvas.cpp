#include "mycanvas.h"
#include "spritesheet.h"
#include <iostream>
#include <string>
#include <QDir>
#include <QDebug>
#include <SFML/OpenGL.hpp>

float MyCanvas::getNote(int note)
{
    //return 72 + note * 7.5;
    double step = ((double) this->height() / 15.0) / 2.0;

    return ((double) (this->height() / 15.0) + ((double) (this->height() / 9.0) - 0.5))
            + step * note;
}

MyCanvas::MyCanvas(QWidget* Parent) : QSFMLCanvas(Parent)
{
    // starting at 1000 so that the notes dont show up at the beginning of the canvas already
    nextNoteIndex = 1000;
    bpm = 90;
    margin = 5;
    timeMargin = 1000;
    currentNote = 0;
    lNoteAmount = 0;
    lNotesCorrect = 0;
    lNotesPassed = 0;
    clefTex = new sf::Texture;
    clefTex->loadFromFile("../resources/clef.png");
    sheet = new SpriteSheet("../spriteSheets/notesSpriteSheet.png", 1, 5);
}

MyCanvas::~MyCanvas()
{
    //delete world;
}

void MyCanvas::OnInit()
{
    b2Vec2 grav(0.0f, 30.0f);
    world = new b2World(grav);

    myClock.restart();
}

void MyCanvas::clear()
{
    nextNoteIndex = 1000;

    for (QList<Shape> lShape : shapes.values())
    {
        for (Shape s : lShape)
        {
            toDelete.push_back(s);
        }
    }

    shapes.clear();
    toDelete.clear();
    toCreate.clear();
}

void MyCanvas::drawStaff()
{
    // Guiding variables
    int barSpacing = this->height() / 15;
    int barThinkness = barSpacing / 5;
    int barStartingY = this->height() / 3;

    // Draw gray guide bar
    sf::RectangleShape guide(sf::Vector2f(4, barSpacing * 6));
    guide.setPosition(this->width() / 2 - 2, barStartingY - barSpacing);
    guide.setFillColor(sf::Color(120, 120, 120));
    RenderWindow::draw(guide);

    // Draw Treble Clef
    double clefScale = (double) (barSpacing * 4) / (double) clefTex->getSize().y;
    sf::RectangleShape clef(sf::Vector2f(clefTex->getSize().x * clefScale * 1.30, clefTex->getSize().y * clefScale * 1.30));
    clef.setPosition(0, barStartingY);
    clef.setTexture(clefTex);
    RenderWindow::draw(clef);

    // Draw staff bars
    for(int i = 0; i < 5; i++)
    {
        sf::RectangleShape shape(sf::Vector2f(this->width() + 10, barThinkness));
        shape.setPosition(sf::Vector2f(-5, barStartingY + (i * barSpacing)));
        shape.setFillColor(sf::Color::Black);
        RenderWindow::draw(shape);
    }
}

int MyCanvas::create(float x, float y, sf::Texture* tex, int key, bool sharp, int ledger)
{
    Shape shape (x, y);
    shape.setAsRectangle(10, 16);
    ShapeContainer container;
    container.shape = shape;
    container.accel = b2Vec2(-5, 0);
    container.gravScale = 0;
    container.set = 0x0000;
    container.noteIndex = nextNoteIndex;
    container.tex = tex;
    container.key = key;
    container.sharp = sharp;
    container.ledger = ledger;
    toCreate.push_back(container);
    return ++nextNoteIndex;
}

void MyCanvas::createFromNoteSignal(int note, NoteLength noteLength)
{
    createFromNote(note, noteLength, false);
}

/**
 * Displayes a not at a given time
 * @brief MyCanvas::createFromNote
 * @param note
 * A note value that goes from 53 to 84
 *
 * @param noteLength
 * Enum that corresponds to the length of the note
 *
 * @param offset
 * Place in milliseconds in which the note will start
 *
 * @return
 */
int MyCanvas::createFromNote(int note, NoteLength noteLength, bool testPage)
{
    // TODO : Load in sprite here, depending on noteLength and if it is a sharp note or not.
    sf::Texture* tex = (*sheet)[(int) noteLength];

    float time = this->width() / 2;

    if (testPage)
    {
        time = this->width() / 2;
    }

    switch (note)
    {
        // F/F# Notes
        case 53:
            return create(time, getNote(10), tex, note, false, 3);
        case 54:
            return create(time, getNote(10), tex, note, true, 3);
        case 65:
            return create(time, getNote(3), tex, note, false, 0);
        case 66:
            return create(time, getNote(3), tex, note, true, 0);
        case 77:
            return create(time, getNote(-4), tex, note, false, 0);
        case 78:
           return create(time, getNote(-4), tex, note, true, 0);
        // G/G# Notes
        case 55:
            return create(time, getNote(9), tex, note, false, 3);
        case 56:
            return create(time, getNote(9), tex, note, true, 3);
        case 67:
            return create(time, getNote(2), tex, note, false, 0);
        case 68:
            return create(time, getNote(2), tex, note, true, 0);
        case 79:
            return create(time, getNote(-5), tex, note, false, 0);
        case 80:
            return create(time, getNote(-5), tex, note, true, 0);
        // A/A# Notes
        case 57:
            return create(time, getNote(8), tex, note, false, 2);
        case 58:
            return create(time, getNote(8), tex, note, true, 2);
        case 69:
            return create(time, getNote(1), tex, note, false, 0);
        case 70:
            return create(time, getNote(1), tex, note, true, 0);
        case 81:
            return create(time, getNote(-6), tex, note, false, -1);
        case 82:
            return create(time, getNote(-6), tex, note, true, -1);
        // B Notes
        case 59:
            return create(time, getNote(7), tex, note, false, 2);
        case 71:
            return create(time, getNote(0), tex, note, false, 0);
        case 83:
            return create(time, getNote(-7), tex, note, false, -1);
        // C/C# Notes
        case 60:
            return create(time, getNote(6), tex, note, false, 1);
        case 61:
            return create(time, getNote(6), tex, note, true, 1);
        case 72:
            return create(time, getNote(-1), tex, note, false, 0);
        case 73:
            return create(time, getNote(-1), tex, note, true, 0);
        case 84:
            return create(time, getNote(-8), tex, note, false, -2);
        // D/D# Notes
        case 62:
            return create(time, getNote(5), tex, note, false, 1);
        case 63:
            return create(time, getNote(5), tex, note, true, 1);
        case 74:
            return create(time, getNote(-2), tex, note, false, 0);
        case 75:
            return create(time, getNote(-2), tex, note, true, 0);
        // E Notes
        case 64:
            return create(time, getNote(4), tex, note, false, 0);
        case 76:
            return create(time, getNote(-3), tex, note, false, 0);
    }
    return -1;
}

void MyCanvas::getKeyPressed(int note, bool testPage) {
    if (testPage)
    {
        createFromNote(note, NoteLength::WholeNote, testPage);
        return;
    }
    if(note != 0)
    {
        currentNote = note;
        userClick = timer.elapsed();
    }
}

void MyCanvas::getKeyReleased(int note, bool testPage) {
    currentNote = 0;
    userClick = 0;
}

void MyCanvas::OnUpdate()
{
    bool lessonEnd = false;

    sf::Event event;
    while (pollEvent(event))
    {
        if (event.type == sf::Event::Resized)
        {

        }
        if (event.type == sf::Event::MouseButtonPressed)
        {

        }
    }

    RenderWindow::clear(sf::Color::White);
    drawStaff();

    for (Shape s : toDelete)
    {
        world->DestroyBody(s.getBody());
    }

    toDelete.clear();

    world->Step(timeStep, velocityIterations, positionIterations);

    for(QList<Shape> lShape : shapes)
    {
        for (Shape s : lShape)
        {
            s.update();
            sf::Shape &source = s.getShape();

            sf::Vector2f scale((double) width() / (double) 380, (double)height() / (double) 220);
            sf::Vector2f newPos = source.getPosition();
            newPos.x *= scale.x;
            //newPos.y *= scale.y;
            newPos.y += (5 + (this->height() / 15) + 0.5);

            sf::RectangleShape shape(sf::Vector2f(35 * scale.x, 56 * scale.y));
            shape.setPosition(newPos);
            shape.setTexture(source.getTexture());
            RenderWindow::draw(shape);

            if (s.isSharp())
            {
                sf::RectangleShape sharpShape(sf::Vector2f(20 * scale.x, 32 * scale.y));
                sf::Texture* sharpTex = (*sheet)[(int) NoteLength::Sharp];
                sharpShape.setTexture(sharpTex);
                sf::Vector2f sharpPos;
                sharpPos.x = newPos.x - shape.getSize().x / 4;
                sharpPos.y = newPos.y + shape.getSize().y / 2;
                sharpShape.setPosition(sharpPos);
                RenderWindow::draw(sharpShape);
            }

            int ledgers = s.getLedger();
            if (ledgers != 0)
            {
                int barSpacing = this->height() / 15;
                int barThinkness = barSpacing / 5;
                int barStartingY = this->height() / 3;

                if (ledgers < 0)
                {
                    int startY = barStartingY;

                    for (int i = -1; i >= ledgers; i--)
                    {
                        sf::RectangleShape ledgerLine(sf::Vector2f(shape.getSize().x, barThinkness));
                        ledgerLine.setPosition(sf::Vector2f(shape.getPosition().x, startY + (i * barSpacing)));
                        ledgerLine.setFillColor(sf::Color::Black);
                        RenderWindow::draw(ledgerLine);
                    }
                }
                else
                {
                    int startY = barStartingY + (barSpacing * 4);

                    for (int i = 1; i <= ledgers; i++)
                    {
                        sf::RectangleShape ledgerLine(sf::Vector2f(shape.getSize().x, barThinkness));
                        ledgerLine.setPosition(sf::Vector2f(shape.getPosition().x - 5, startY + (i * barSpacing)));
                        ledgerLine.setFillColor(sf::Color::Black);
                        RenderWindow::draw(ledgerLine);
                    }
                }
            }

            if (newPos.x > (this->width() / 2 - margin) && newPos.x < (this->width() / 2 + margin)) {
    //            qDebug() << "HIT" << shapes[i].getNoteIndex();
    //            correct(shapes[i]);

                qint64 timeHit = timer.elapsed();
                bool inRange = userClick >= (timeHit - timeMargin)
                        && userClick <= (timeHit + timeMargin);

                if (lNoteAmount > 0)
                {
                    if (s.f && currentNote == s.getKey() && inRange) {
                        s.setGravityScale(-1);
                        s.f = false;
                        lNotesCorrect++;
                    } else if(s.f) {
                        s.setGravityScale(1);
                        s.f = false;
                    }

                    currentNote = 0;
                    lNotesPassed++;
                }

                lessonEnd = lNotesPassed >= lNoteAmount;

                continue;
            }
        }

        /*
        if(shapes[i].getX() < -20 || shapes[i].getY() < -20 || shapes[i].getY() > 500)
        {
            world->DestroyBody(shapes[i].getBody());
            shapes.erase(shapes.begin() + i);
            i--;
            continue;
        }*/
    }

    if (lessonEnd && lNoteAmount > 0)
    {
        emit sendLessonEnd(lNoteAmount, lNotesCorrect);
    }

    for (ShapeContainer container : toCreate)
    {
        Shape shape = container.shape;
        shape.createBody(world);
        shape.setLinearVelocity(container.accel);
        shape.setGravityScale(container.gravScale);
        shape.set(container.set);
        shape.setNoteIndex(container.noteIndex);
        shape.setTexture(container.tex);
        shape.setKey(container.key);
        shape.setSharp(container.sharp);
        shape.setLedger(container.ledger);
        shapes[shape.getKey()].push_back(shape);
    }

    toCreate.clear();

    myClock.restart();
}

void MyCanvas::queueLessonLoad(int lesson)
{
    QString filePath = "../midFiles/lesson" + QString::number(lesson) + ".mid";

    midi_tool.openFile(filePath.toStdString());
    lNoteAmount = 0;
    lNotesCorrect = 0;
    lNotesPassed = 0;

    //midi_tool.openFile("../midFiles/twinkle.mid");

    timer.start();
    queueNextNote();
}

void MyCanvas::queueNextNote()
{
    midi_tool.getNextNote();

    if (midi_tool.EOFPassed())
    {
        return;
    }

    double whole = midi_tool.getQuarterNoteLengthInSeconds() * 4;
    double nLen = midi_tool.getNoteLength();

    double div = whole / nLen;
    NoteLength lenEnum;

    switch ((int) std::round(div))
    {
        case 2:
            lenEnum = NoteLength::HalfNote;
            break;
        case 4:
            lenEnum = NoteLength::QuarterNote;
            break;
        case 8:
            lenEnum = NoteLength::EigthNote;
            break;
        default:
            lenEnum = NoteLength::WholeNote;
            break;
    }

    createFromNote(midi_tool.getNote(), lenEnum, false);

    double interval = nLen * 1000;
    QTimer::singleShot((int) interval, this, &MyCanvas::queueNextNote);
    lNoteAmount++;
}

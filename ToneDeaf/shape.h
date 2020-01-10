#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Shape
{

public:
    Shape(float x, float y) : position(x, y) {}

    Shape operator =(const Shape &other)
    {
        body = other.body;
        shape = other.shape;
        position = other.position;
        r = other.r;
        g = other.g;
        b = other.b;
        noteValue = other.noteValue;

        return *this;
    }

    void setAsRectangle(float width, float height);

    float getX();
    float getY();
    bool f = true;

    int getNoteIndex();
    void setNoteIndex(int);

    void setLinearVelocity(b2Vec2);
    void applyForce(b2Vec2);
    void setGravityScale(float);
    void set(short);
    void setKey(int);
    void setSharp(bool);
    void setLedger(int);
    int getLedger();
    bool isSharp();
    int getKey();

    const sf::Texture* getTexture();
    void setTexture(const sf::Texture* image);

    void createBody(b2World *world, bool dynamic = true);
    b2Body *getBody() {return body;}
    sf::Shape &getShape() { return *shape; }
    void update();

private:
    sf::Vector2f position;
    sf::Shape* shape;
    b2Body* body;
    int noteIndex;
    int noteValue;
    bool sharp = false;
    int ledger = 0;

    short fixt;

    int r = rand() % 256, g = rand() % 256, b = rand() % 256;

    const int worldScale = 30;
};

#endif // SHAPE_H

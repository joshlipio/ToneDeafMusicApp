#ifndef SHAPECONTAINER_H
#define SHAPECONTAINER_H

#include "shape.h"
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"


class ShapeContainer
{
public:
    ShapeContainer();
    Shape shape;
    b2Vec2 accel;
    int gravScale;
    int set;
    int noteIndex;
    sf::Texture* tex;
    int key;
    bool sharp;
    int ledger;
};

#endif // SHAPECONTAINER_H

#include "shape.h"

const sf::Texture* Shape::getTexture()
{
    return shape->getTexture();
}

void Shape::setTexture(const sf::Texture* image)
{
    shape->setTexture(image);
}

void Shape::setAsRectangle(float width, float height)
{
    sf::RectangleShape *rectangle = new sf::RectangleShape(sf::Vector2f(width, height));
    rectangle->setPosition(position);
    rectangle->setOrigin(width / 2, height / 2);
    shape = rectangle;
}

float Shape::getX()
{
    return body->GetPosition().x;
}

float Shape::getY()
{
    return body->GetPosition().y;
}

void Shape::setLinearVelocity(b2Vec2 vec)
{
    body->SetLinearVelocity(vec);
}

void Shape::applyForce(b2Vec2 vec)
{
    body->ApplyForceToCenter(vec, true);
}

void Shape::setGravityScale(float scale)
{
    body->SetGravityScale(scale);
}

void Shape::set(short val)
{
    b2Filter filter = body->GetFixtureList()->GetFilterData();
    filter.maskBits = val;
    body->GetFixtureList()->SetFilterData(filter);
}

void Shape::setKey(int key)
{
    noteValue = key;
}

void Shape::setSharp(bool sh)
{
    sharp = sh;
}

bool Shape::isSharp()
{
    return sharp;
}

void Shape::setLedger(int num)
{
    ledger = num;
}

int Shape::getLedger()
{
    return ledger;
}

int Shape::getKey()
{
    return noteValue;
}

void Shape::createBody(b2World* world, bool dynamic)
{
    //shape->setFillColor(sf::Color(r, g, b));

    while (world->IsLocked())
    {

    }

    b2BodyDef bodyDef;
    if (dynamic) bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / worldScale, position.y / worldScale);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(shape->getLocalBounds().width / 2 / worldScale, shape->getLocalBounds().height / 2 / worldScale);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = dynamic;
    fixtureDef.friction = 0.001f;
    body->CreateFixture(&fixtureDef);
}

void Shape::update()
{
    shape->setPosition(body->GetPosition().x * worldScale, body->GetPosition().y * worldScale);
    shape->setRotation(body->GetAngle() * 180 / b2_pi);
}

int Shape::getNoteIndex()
{
    return noteIndex;
}

void Shape::setNoteIndex(int idx)
{
    noteIndex = idx;
}

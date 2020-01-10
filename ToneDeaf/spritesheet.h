#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <QString>

#include <SFML/Graphics.hpp>

class SpriteSheet
{
public:
    SpriteSheet(QString sheetPath, int rows, int columns);
    SpriteSheet(SpriteSheet const &other);
    ~SpriteSheet();

    sf::Texture*& operator [](int idx)
    {
        return sprites[idx];
    }
    sf::Texture* operator [](int idx) const
    {
        return sprites[idx];
    }

private:
    std::vector<sf::Texture*> sprites;
};

#endif // SPRITESHEET_H

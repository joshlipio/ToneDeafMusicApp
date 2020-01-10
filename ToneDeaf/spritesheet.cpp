#include "spritesheet.h"

SpriteSheet::SpriteSheet(QString sheetPath, int rows, int columns)
{
    sf::Image img;
    img.loadFromFile(sheetPath.toStdString());
    int xoffset = img.getSize().x / columns;
    int yoffset = img.getSize().y / rows;

    for (int i = 0; i < img.getSize().y; i += yoffset)
    {
        for (int j = 0; j < img.getSize().x; j += xoffset)
        {
            sf::Texture* tex = new sf::Texture();
            tex->loadFromFile(sheetPath.toStdString(), sf::IntRect(j, i, xoffset, yoffset));
            sprites.push_back(tex);
        }
    }
}

SpriteSheet::SpriteSheet(const SpriteSheet &other)
{
    sprites = other.sprites;
}

SpriteSheet::~SpriteSheet()
{
}

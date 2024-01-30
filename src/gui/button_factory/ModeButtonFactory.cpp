#include <ModeButtonFactory.hpp>

SpriteButtonView::Ptr ModeButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position)
{
    sf::IntRect textureRects[3]
    {
        sf::IntRect(0, 0, 35, 35),
        sf::IntRect(35, 0, 35, 35),
        sf::IntRect(35, 0, 35, 35)
    };

    SpriteButtonView::Ptr logOutButton = std::make_unique<SpriteButtonView>(context, texture, font, textureRects, "", 0, position, sf::Vector2f(35, 35));

    return std::move(logOutButton);
}
#include <EditDictButtonFactory.hpp>

SpriteButtonView::Ptr EditDictButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::IntRect textureRects[3]
    {
        sf::IntRect(0, 0, 25, 23),
        sf::IntRect(25, 0, 25, 23),
        sf::IntRect(25, 0, 25, 23)
    };

    const sf::Vector2f buttonSize(25, 23);
    SpriteButtonView::Ptr editDictButtonView = std::make_unique<SpriteButtonView>(context, texture, font, textureRects, "", 0, position, buttonSize);

    editDictButtonView->setOnMouseButtonReleased(callback);
    
    return std::move(editDictButtonView);
}

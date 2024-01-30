#include <SetLangButtonFactory.hpp>

ColoredButtonView::Ptr SetLangButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::Vector2f buttonSize(200, 70);
    sf::Color buttonColors[3]
    {
        sf::Color::Transparent,
        sf::Color(255, 255, 255, 85),
        sf::Color(255, 255, 255, 85)
    };

    SpriteView::Ptr spriteView = std::make_unique<SpriteView>(context, texture, sf::Vector2f(), sf::Vector2f(50, 50));
    spriteView->setPosition((buttonSize.x - spriteView->get().getGlobalBounds().getSize().x) / 2.f, 10);

    ColoredButtonView::Ptr setLangButtonView = std::make_unique<ColoredButtonView>(context, font, "", position, buttonSize, buttonColors);

    setLangButtonView->setOnMouseButtonReleased(callback);

    setLangButtonView->attachView(std::move(spriteView));
    return std::move(setLangButtonView);
}
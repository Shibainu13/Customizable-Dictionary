#include <FavButtonFactory.hpp>

ColoredButtonView::Ptr FavButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::Vector2f buttonSize(99, 70);
    sf::Color buttonColors[3]
    {
        sf::Color::Transparent,
        sf::Color(255, 255, 255, 85),
        sf::Color(255, 255, 255, 85)
    };

    TextView::Ptr textView = std::make_unique<TextView>(context, "Favorite", font, sf::Vector2f(), 18, sf::Color(248, 241, 241));
    textView->setPosition((buttonSize.x - textView->getGlobalBounds().getSize().x) / 2.f, 51);

    SpriteView::Ptr spriteView = std::make_unique<SpriteView>(context, texture, sf::Vector2f(), sf::Vector2f(48, 46));
    spriteView->setPosition((buttonSize.x - spriteView->get().getGlobalBounds().getSize().x) / 2.f, 6);

    ColoredButtonView::Ptr favButtonView = std::make_unique<ColoredButtonView>(context, font, "", position, buttonSize, buttonColors);

    favButtonView->setOnMouseButtonReleased(callback);

    favButtonView->attachView(std::move(textView));
    favButtonView->attachView(std::move(spriteView));

    return std::move(favButtonView);
}
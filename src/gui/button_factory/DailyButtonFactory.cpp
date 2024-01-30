#include <DailyButtonFactory.hpp>

ColoredButtonView::Ptr DailyButtonFactory::create(Activity *context, const sf::Texture &texture, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback callback)
{
    sf::Vector2f buttonSize(99, 70);
    sf::Color buttonColors[3]
    {
        sf::Color::Transparent,
        sf::Color(255, 255, 255, 85),
        sf::Color(255, 255, 255, 85)
    };
    
    TextView::Ptr textView = std::make_unique<TextView>(context, "Daily", font, sf::Vector2f(), 18, sf::Color(248, 241, 241));
    textView->setPosition((buttonSize.x - textView->getGlobalBounds().getSize().x) / 2.f, 51);

    SpriteView::Ptr spriteView = std::make_unique<SpriteView>(context, texture, sf::Vector2f(), sf::Vector2f(48, 44));
    spriteView->setPosition((buttonSize.x - spriteView->get().getGlobalBounds().getSize().x) / 2.f, 3);

    ColoredButtonView::Ptr dailyButtonView = std::make_unique<ColoredButtonView>(context, font, "", position, buttonSize, buttonColors);

    dailyButtonView->setOnMouseButtonReleased(callback);

    dailyButtonView->attachView(std::move(textView));
    dailyButtonView->attachView(std::move(spriteView));

    return std::move(dailyButtonView);
}
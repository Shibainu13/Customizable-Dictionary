#include <NewWordFactory.hpp>

EditTextView::Ptr NewWordFactory::create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position)
{
    const sf::Vector2f newWordTextSize(600.f, 44.f);
    EditTextView::Ptr newWordText = std::make_unique<EditTextView>(publisher, font, text, 35, position, newWordTextSize);
    newWordText->setFocusBackgroundColor(sf::Color(17, 105, 142));
    newWordText->setUnfocusBackgroundColor(sf::Color(17, 105, 142));
    newWordText->setTextColor(sf::Color(255, 255, 255, 175));
    newWordText->setAlignment(EditTextView::Alignment::CENTER);

    newWordText->setOnTextEntered([&](EventListener *listener, const sf::Event &event) {});
    newWordText->setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});

    return std::move(newWordText);
}
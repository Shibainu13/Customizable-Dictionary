#include <NewWordTypeFactory.hpp>

EditTextOnScrollView::Ptr NewWordTypeFactory::create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, ScrollRectView *scrollRect)
{
    const sf::Vector2f newWordTypeSize(890.f, 41.f);
    const unsigned int charSize = 30;
    EditTextOnScrollView::Ptr newWordTypeTextBox = std::make_unique<EditTextOnScrollView>(publisher, font, text, charSize, position, newWordTypeSize, scrollRect);
    newWordTypeTextBox->setTextColor(sf::Color(17, 105, 142));
    newWordTypeTextBox->setUnfocusBackgroundColor(sf::Color::White);
    newWordTypeTextBox->setFocusBackgroundColor(sf::Color::White);
    newWordTypeTextBox->setUnFocusBorder(sf::Color::Transparent, 0.2);
    newWordTypeTextBox->setFocusBorder(sf::Color(17, 105, 142), 0.2);

    newWordTypeTextBox->setOnTextEntered([&](EventListener *listener, const sf::Event &event) {});
    newWordTypeTextBox->setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});

    return std::move(newWordTypeTextBox);
}
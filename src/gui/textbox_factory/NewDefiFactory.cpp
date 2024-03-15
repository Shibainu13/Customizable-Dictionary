#include <NewDefiFactory.hpp>

EditTextOnScrollView::Ptr NewDefiFactory::create(Activity *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, ScrollRectView *rectView, EventListener::EventCallback onTextEntered)
{
    const sf::Vector2f newDefiSize(890.f, 27.f);
    const unsigned int charSize = 20;
    EditTextOnScrollView::Ptr newDefiTextBox = std::make_unique<EditTextOnScrollView>(publisher, font, text, charSize, position, newDefiSize, rectView);
    newDefiTextBox->setWrapEnabled(true);
    newDefiTextBox->setTextColor(sf::Color::Black);
    newDefiTextBox->setUnfocusBackgroundColor(sf::Color::White);
    newDefiTextBox->setFocusBackgroundColor(sf::Color::White);

    newDefiTextBox->setOnTextEntered(onTextEntered);
    newDefiTextBox->setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});

    return std::move(newDefiTextBox);
}
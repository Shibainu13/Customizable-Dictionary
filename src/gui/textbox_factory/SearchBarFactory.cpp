#include <SearchBarFactory.hpp>

EditTextView::Ptr SearchBarFactory::create(Activity *context, const sf::Font &cursorFont, const sf::Font &font, const sf::Vector2f &position, EventListener::EventCallback onTextEnterd, EventListener::EventCallback onMouseButtonPressed)
{
    int searchBarCharacterSize = 20;
    sf::Vector2f searchBarSize(372, 21);
    EditTextView::Ptr searchBarView = std::make_unique<EditTextView>(context, cursorFont, font, searchBarCharacterSize, "", position, searchBarSize);

    searchBarView->setOnTextEntered(onTextEnterd);
    searchBarView->setOnMouseButtonReleased(onMouseButtonPressed);

    return std::move(searchBarView);
}
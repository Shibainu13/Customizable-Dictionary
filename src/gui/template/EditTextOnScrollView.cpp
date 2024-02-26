#include <EditTextOnScrollView.hpp>

EditTextOnScrollView::EditTextOnScrollView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, ScrollRectView *rectView)
    : EditTextView(publisher, font, text, characterSize, position, size), rectView(rectView)
{
}

void EditTextOnScrollView::setOnMouseButtonReleased(EventCallback onMouseButtonReleased)
{
    EventDoubleCallback onDoubleCallback = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        EditTextOnScrollView *editTextView = dynamic_cast<EditTextOnScrollView *>(listener);
        if (editTextView->getGlobalBounds().contains(rectView->getRectMouseCoords()))
        {
            setFocused(true);
            setBackgroundColor(mFocusBackgroundColor);
            resetBlink();
        }
        else
        {
            setFocused(false);
            setBackgroundColor(mUnfocusBackgroundColor);
        }
        callback(listener, event);
    };
    EventCallback onEvent = std::bind(onDoubleCallback, std::placeholders::_1, std::placeholders::_2, onMouseButtonReleased);
    EventListener::setOnMouseButtonReleased(onEvent);
}
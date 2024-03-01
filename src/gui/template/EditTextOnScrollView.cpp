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

void EditTextOnScrollView::updateTextPosition()
{
    mText.setOrigin(0, 0);
    mText.setPosition(0, 0);
    mCursor.setOrigin(0, 0);
    mCursor.setPosition(0, 0);

    if (alignment == Alignment::LEFT)
    {
        mText.setPosition(mRect.getPosition());
        mCursor.setOrigin(mCursor.getGlobalBounds().getPosition() + sf::Vector2f(0, mCursor.getGlobalBounds().getSize().y / 2.f));
        mCursor.setPosition(mText.getPosition() + sf::Vector2f(mText.getGlobalBounds().getSize().x + 2, mRect.getSize().y / 2.f));
    }
    else if (alignment == Alignment::CENTER)
    {
        mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
        mText.setPosition(mRect.getSize() / 2.f);
        mCursor.setOrigin(mCursor.getGlobalBounds().getPosition() + sf::Vector2f(0, mCursor.getGlobalBounds().getSize().y / 2.f));
        mCursor.setPosition(mText.getPosition() + sf::Vector2f(mText.getGlobalBounds().getSize().x / 2.f + 2, 0.f));
    }
}
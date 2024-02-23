#include <EditTextView.hpp>

EditTextView::EditTextView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &size)
    : EditTextView(publisher, font, text, 20, sf::Vector2f(0, 0), size)
{
}

EditTextView::EditTextView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size)
    : EditTextView(publisher, font, text, 20, position, size)
{
}

EditTextView::EditTextView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size)
    : EditTextView(publisher, font, font, characterSize, text, position, size)
{
}

EditTextView::EditTextView(EventPublisher *publisher, const sf::Font &cursorFont, const sf::Font &font, unsigned int characterSize, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size)
    : ViewGroup(publisher), mRect(size), mText(text, font, characterSize), mCursor("|", cursorFont, characterSize), mIsFocused(false), alignment(Alignment::LEFT)
{
    mString = text;
    setPosition(position);
    setTextColor(sf::Color::Black);
    updateTextPosition();

    setFocusBackgroundColor(sf::Color(245, 245, 245));
    setUnfocusBackgroundColor(sf::Color(245, 245, 245));
    setBackgroundColor(mUnfocusBackgroundColor);

    setBlinkTime(sf::seconds(0.5f));
    resetBlink();

    setInputType(InputType::TEXT);

    setOnMouseButtonPressed([&](EventListener *listener, const sf::Event &event) {});

    setOnTextEntered([&](EventListener *listener, const sf::Event &event) {});
}

void EditTextView::setOnTextEntered(EventCallback onTextEntered)
{
    EventDoubleCallback onDoubleCallback = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        sf::Uint32 unicode = event.text.unicode;
        if (isFocused())
        {
            resetBlink();
            if (unicode == 8) // backspace
                removeCharacter();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) // enter
                setFocused(false);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // escape
                setFocused(false);
            else if (isprint(unicode))
                appendCharacter(event.key.code);
        }
        callback(listener, event);
    };
    EventCallback onEvent = std::bind(onDoubleCallback, std::placeholders::_1, std::placeholders::_2, onTextEntered);
    EventListener::setOnTextEntered(onEvent);
}

void EditTextView::setOnMouseButtonReleased(EventCallback onMouseButtonReleased)
{
    EventDoubleCallback onDoubleCallback = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        if (isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
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

void EditTextView::setInputType(InputType type)
{
    mInputType = type;
    setText(mString);
}

void EditTextView::updateTextPosition()
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

void EditTextView::setBackgroundColor(const sf::Color &color)
{
    mRect.setFillColor(color);
}

void EditTextView::setFocusBackgroundColor(const sf::Color &color)
{
    mFocusBackgroundColor = color;
    updateBackgroundColor();
}

void EditTextView::setUnfocusBackgroundColor(const sf::Color &color)
{
    mUnfocusBackgroundColor = color;
    updateBackgroundColor();
}

void EditTextView::updateBackgroundColor()
{
    if (isFocused())
        setBackgroundColor(mFocusBackgroundColor);
    else
        setBackgroundColor(mUnfocusBackgroundColor);
}

void EditTextView::setTextColor(const sf::Color &color)
{
    mText.setFillColor(color);
    mCursor.setFillColor(color);
}

void EditTextView::setText(const std::string &text)
{
    if (mInputType == InputType::PASSWORD)
    {
        std::string password(text.size(), '*');
        mText.setString(password);
    }
    else if (mInputType == InputType::TEXT)
        mText.setString(text);

    mString = text;
    updateTextPosition();
}

void EditTextView::appendCharacter(char character)
{
    std::string formerText = mText.getString();
    mText.setString(formerText + character);
    if (mText.getGlobalBounds().getSize().x <= mRect.getSize().x)
        setText(formerText + character);
    else
        setText(formerText);
    // mText.setString(mText.getString() + character);
}

void EditTextView::removeCharacter()
{
    if (mText.getString().getSize() > 0)
        setText(mText.getString().substring(0, mText.getString().getSize() - 1));
}

void EditTextView::clearText()
{
    setText("");
}

const std::string &EditTextView::getText() const
{
    return mString;
}

sf::FloatRect EditTextView::getGlobalBounds() const
{
    return getWorldTransform().transformRect(mRect.getGlobalBounds());
}

bool EditTextView::isOnMouseButtonPressed(const sf::Event &event) const
{
    // return getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
    return true;
}

bool EditTextView::isMouseHovering(const sf::Vector2f &mousePoint) const
{
    return getGlobalBounds().contains(mousePoint);
}

bool EditTextView::isOnTextEntered(const sf::Event &event) const
{
    return isFocused();
}

bool EditTextView::isFocused() const
{
    return mIsFocused;
}

void EditTextView::setFocused(bool focused)
{
    mIsFocused = focused;
    updateBackgroundColor();
}

void EditTextView::updateCurrent(sf::Time delta)
{
    mCurrentTime += delta;
    if (mCurrentTime >= mCursorBlinkTime)
    {
        mCurrentTime -= mCursorBlinkTime;
        mCursorVisible = !mCursorVisible;
    }
}

void EditTextView::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mRect, states);
    target.draw(mText, states);
    if (mCursorVisible && isFocused())
        target.draw(mCursor, states);
}

void EditTextView::setBlinkTime(sf::Time time)
{
    mCursorBlinkTime = time;
}

void EditTextView::resetBlink()
{
    mCurrentTime = sf::Time::Zero;
    mCursorVisible = true;
}

void EditTextView::setAlignment(Alignment alignment)
{
    this->alignment = alignment;
    updateTextPosition();
}
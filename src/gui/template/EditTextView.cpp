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
    : ViewGroup(publisher), mRect(size, 0.f, 4), mText(text, font, characterSize), mCursor("|", cursorFont, characterSize), mIsFocused(false), mWrapEnabled(false), alignment(Alignment::LEFT), numLines(1), mWrapUp(false), mDropdown(false)
{
    mString = text;
    setPosition(position);
    setTextColor(sf::Color::Black);
    updateTextPosition();

    setFocusBackgroundColor(sf::Color(245, 245, 245));
    setUnfocusBackgroundColor(sf::Color(245, 245, 245));
    setBackgroundColor(mUnfocusBackgroundColor);

    setUnFocusBorder(sf::Color::Transparent, 0.f);
    setFocusBorder(sf::Color::Transparent, 0.f);
    setBorderColor(mUnFocusBorderColor, 0.f);

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
    if (mWrapEnabled)
        for (int i = mString.size() - 1; i >= 0; i--)
        {
            if (mString.at(i) == '\n')
            {
                mString.erase(i, 1);
                mString.insert(i, " ");
            }
        }
    updateTextPosition();
}

void EditTextView::appendCharacter(char character)
{
    if (mWrapEnabled) // remove the cursor
        setText(mText.getString().substring(0, mText.getString().getSize() - 1));

    std::string formerText = getText();
    mText.setString(formerText + character);
    if (mText.getGlobalBounds().getSize().x <= mRect.getSize().x)
        setText(formerText + character);
    else if (mWrapEnabled && numLines <= DEFAULT_LINE_LIMIT && mText.getGlobalBounds().getSize().x > mRect.getGlobalBounds().getSize().x)
        dropdown();
    else
        setText(formerText);

    if (mWrapEnabled)
        setText(mText.getString() + "|");
}

void EditTextView::dropdown()
{
    for (int i = 0; i < mText.getString().getSize(); i++)
    {
        if (mText.findCharacterPos(i).x > mRect.getGlobalBounds().getSize().x)
        {
            for (int j = i; j >= 0; j--)
            {
                if (mText.getString()[j] == ' ')
                {
                    sf::String str = mText.getString();
                    str.erase(j, 1);
                    str.insert(j, "\n");
                    setText(str);
                    numLines++;
                    break;
                }
            }
            mDropdown = true;
        }
    }
    mRect.setSize(sf::Vector2f(mRect.getGlobalBounds().getSize().x, mText.getGlobalBounds().getSize().y));
}

void EditTextView::removeCharacter()
{
    sf::Vector2f lastCharPos;
    if (mWrapEnabled)
        lastCharPos = mText.findCharacterPos(mText.getString().getSize() - 1);

    if (!mWrapEnabled && mText.getString().getSize() > 0)
        setText(mText.getString().substring(0, mText.getString().getSize() - 1));
    else if (mWrapEnabled && mText.getString().getSize() > 1)
    {
        setText(mText.getString().substring(0, mText.getString().getSize() - 2));
        setText(mText.getString() + "|");
    }
    if (mWrapEnabled && mText.findCharacterPos(mText.getString().getSize() - 1).y != lastCharPos.y)
    {
        --numLines;
        mWrapUp = true;
        mRect.setSize(sf::Vector2f(mRect.getGlobalBounds().getSize().x, mText.getGlobalBounds().getSize().y));
    }
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

int EditTextView::getNumLines() const
{
    return numLines;
}

void EditTextView::setFocused(bool focused)
{
    if (mIsFocused == focused)
        return;
    mIsFocused = focused;
    updateBackgroundColor();
    updateBorderColor();
    if (mIsFocused && mWrapEnabled)
        setText(mText.getString() + "|");
    else if (!mIsFocused && mWrapEnabled)
        setText(mText.getString().substring(0, mText.getString().getSize() - 1));
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
    if (!mWrapEnabled && mCursorVisible && isFocused())
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

void EditTextView::setWrapEnabled(bool enable)
{
    mWrapEnabled = enable;
    if (mWrapEnabled)
    {
        dropdown();
    }
}

void EditTextView::setFocusBorder(const sf::Color &color, float thickness)
{
    mFocusBorderColor = color;
    focusThickness = thickness;
    updateBorderColor();
}

void EditTextView::setUnFocusBorder(const sf::Color &color, float thickness)
{
    mUnFocusBorderColor = color;
    unfocusThickness = thickness;
    updateBorderColor();
}

void EditTextView::setBorderColor(const sf::Color &color, float thickness)
{
    mRect.setOutlineColor(color);
    mRect.setOutlineThickness(thickness);
}

void EditTextView::updateBorderColor()
{
    if (isFocused())
        setBorderColor(mFocusBorderColor, focusThickness);
    else
        setBorderColor(mUnFocusBorderColor, unfocusThickness);
}

bool EditTextView::alertDropdown() const
{
    return mDropdown;
}

bool EditTextView::alertWrapUp() const
{
    return mWrapUp;
}

void EditTextView::disableAlerts()
{
    mDropdown = false;
    mWrapUp = false;
}

void EditTextView::setCornersRadius(float radius)
{
    mRect.setCornersRadius(radius);
}
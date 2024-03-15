#include <ButtonView.hpp>

ButtonView::ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text)
    : ButtonView(publisher, texture, font, text, sf::Vector2f(0, 0))
{
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, const sf::Vector2f &position)
    : ButtonView(publisher, texture, font, text, position, sf::Vector2f(texture.getSize()))
{
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size)
    : ButtonView(publisher, texture, font, text, 30, position, size)
{
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size)
    : ViewGroup(publisher), mSprite(texture), mShape(new sf::RectangleShape(size)), mText(text, font, characterSize)
{
    setPosition(position);
    mShape->setFillColor(sf::Color::Transparent);
    mSprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(size / 2.f);
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::IntRect &textureRect)
    : ViewGroup(publisher), mSprite(texture, textureRect), mShape(new sf::RectangleShape(sf::Vector2f(textureRect.width, textureRect.height))), mText(text, font, characterSize)
{
    setPosition(position);
    mShape->setFillColor(sf::Color::Transparent);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(textureRect.width / 2, textureRect.height / 2);
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::IntRect &textureRect, const sf::Vector2f &size)
    : ViewGroup(publisher), mSprite(texture, textureRect), mShape(new sf::RectangleShape(size)), mText(text, font, characterSize)
{
    setPosition(position);
    mShape->setFillColor(sf::Color::Transparent);
    // mShape.setFillColor(sf::Color::Red);
    mSprite.setScale(size.x / textureRect.width, size.y / textureRect.height);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(size / 2.f);
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &size, const sf::Color &fillColor)
    : ButtonView(publisher, font, text, 30, sf::Vector2f(0, 0), size, fillColor)
{
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor)
    : ButtonView(publisher, font, text, 30, position, size, fillColor)
{
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor)
    : ViewGroup(publisher), mSprite(), mShape(new sf::RectangleShape(size)), mText(text, font, characterSize)
{
    setPosition(position);
    mShape->setFillColor(fillColor);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(size / 2.f);
}

ButtonView::ButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::IntRect &textureRect, const sf::Vector2f &size, const sf::Vector2f &spriteSize)
    : ViewGroup(publisher), mSprite(texture, textureRect), mShape(new sf::RectangleShape(size)), mText(text, font, characterSize)
{
    setPosition(position);
    mShape->setFillColor(sf::Color::Transparent);
    // rescaleTexture(spriteSize);
    centerSprite();
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(size / 2.f);
}

ButtonView::~ButtonView()
{
    if (mShape)
        delete mShape;
}

void ButtonView::setTexture(const sf::Texture &texture, bool resetRect)
{
    mSprite.setTexture(texture, resetRect);
    // mShape.setSize(sf::Vector2f(texture.getSize()));
}

void ButtonView::setTextureRect(const sf::IntRect &rect)
{
    mSprite.setTextureRect(rect);
    // mShape.setSize(sf::Vector2f(rect.width, rect.height));
}

void ButtonView::setText(const std::string &text)
{
    mText.setString(text);
    mText.setOrigin(0, 0);
    mText.setPosition(0, 0);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(mShape->getGlobalBounds().getSize() / 2.f);
}

void ButtonView::setText(const std::string &text, const sf::Vector2f &relativePos)
{
    mText.setString(text);
    mText.setOrigin(0, 0);
    mText.setPosition(relativePos);
}

void ButtonView::setBackgroundColor(const sf::Color &color)
{
    mShape->setFillColor(color);
}

void ButtonView::setTextColor(const sf::Color &color)
{
    mText.setFillColor(color);
}

sf::FloatRect ButtonView::getGlobalBounds() const
{
    return getWorldTransform().transformRect(mShape->getGlobalBounds());
}

sf::FloatRect ButtonView::getLocalBounds() const
{
    return getWorldTransform().transformRect(mShape->getLocalBounds());
}

bool ButtonView::isMouseHovering(const sf::Vector2f &mousePoint) const
{
    return getGlobalBounds().contains(mousePoint);
}

void ButtonView::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*mShape, states);
    target.draw(mSprite, states);
    target.draw(mText, states);
}

bool ButtonView::isOnMouseButtonPressed(const sf::Event &event) const
{
    return isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

bool ButtonView::isOnMouseButtonReleased(const sf::Event &event) const
{
    return isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

bool ButtonView::isOnMouseMoved(const sf::Event &event) const
{
    return true;
}

void ButtonView::setCircleButton()
{
    // sf::CircleShape circle(mShape.getSize().x / 2.f);
    float radius = mShape->getGlobalBounds().getSize().x / 2.f;
    sf::Color color = mShape->getFillColor();
    sf::Vector2f position = mShape->getPosition();
    if (mShape)
        delete mShape;
    mShape = new sf::CircleShape(radius);
    mShape->setFillColor(color);
    mShape->setPosition(position.x - radius, position.y - radius);
    mShape->setPosition(position);
}

void ButtonView::setBorderColor(const sf::Color &color, float thickness)
{
    mShape->setOutlineThickness(thickness);
    mShape->setOutlineColor(color);
}

void ButtonView::rescaleTexture(const sf::Vector2f &size)
{
    mSprite.setScale(mShape->getGlobalBounds().getSize().x / size.x, mShape->getGlobalBounds().getSize().y / size.y);
}

void ButtonView::centerSprite()
{
    mSprite.setOrigin(mSprite.getGlobalBounds().getPosition() + mSprite.getGlobalBounds().getSize() / 2.f);
    mSprite.setPosition(mShape->getGlobalBounds().getSize().x / 2.f, mShape->getGlobalBounds().getSize().y / 2.f);
}

std::string ButtonView::getText() const
{
    return mText.getString();
}
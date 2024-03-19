#include <RoundedRectangleView.hpp>

RoundedRectangleView::RoundedRectangleView(EventPublisher *publisher, float left, float top, float width, float height, float cornersRadius, unsigned int cornerPointCount)
    : RoundedRectangleView(publisher, sf::Vector2f(width, height), cornersRadius, cornerPointCount, sf::Vector2f(left, top), sf::Color::Black)
{
}

RoundedRectangleView::RoundedRectangleView(EventPublisher *publisher, float left, float top, float width, float height, float cornersRadius, unsigned int cornerPointCount, const sf::Color &color)
    : RoundedRectangleView(publisher, sf::Vector2f(width, height), cornersRadius, cornerPointCount, sf::Vector2f(left, top), color)
{
}

RoundedRectangleView::RoundedRectangleView(EventPublisher *publisher, const sf::Vector2f &size, float cornersRadius, unsigned int cornerPointCount, const sf::Vector2f &position)
    : RoundedRectangleView(publisher, size, cornersRadius, cornerPointCount, position, sf::Color::Black)
{
}

RoundedRectangleView::RoundedRectangleView(EventPublisher *publisher, const sf::Vector2f &size, float cornersRadius, unsigned int cornerPointCount, const sf::Vector2f &position, const sf::Color &color)
    : ViewGroup(publisher), mRect(size, cornersRadius, cornerPointCount)
{
    setPosition(position);
    setFillColor(color);
}

void RoundedRectangleView::setFillColor(sf::Color color)
{
    mRect.setFillColor(color);
}

void RoundedRectangleView::setSize(const sf::Vector2f &size)
{
    mRect.setSize(size);
}

void RoundedRectangleView::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mRect, states);
}

void RoundedRectangleView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    ViewGroup::draw(target, states);
}

sf::FloatRect RoundedRectangleView::getGlobalBounds() const
{
    return getWorldTransform().transformRect(mRect.getGlobalBounds());
}

bool RoundedRectangleView::isMouseHovering(const sf::Vector2f &mousePoint) const
{
    return getGlobalBounds().contains(mousePoint);
}

bool RoundedRectangleView::isOnMouseButtonPressed(const sf::Event &event) const
{
    return isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

bool RoundedRectangleView::isOnMouseButtonReleased(const sf::Event &event) const
{
    return isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

void RoundedRectangleView::setOutineColor(const sf::Color &color)
{
    mRect.setOutlineColor(color);
}

void RoundedRectangleView::setOutlineThickness(float thickness)
{
    mRect.setOutlineThickness(thickness);
}

void RoundedRectangleView::setCornersRadius(float radius)
{
    mRect.setCornersRadius(radius);
}

float RoundedRectangleView::getCornersRadius() const
{
    return mRect.getCornersRadius();
}

void RoundedRectangleView::setCornerPointCount(unsigned int cornerPointCount)
{
    mRect.setCornerPointCount(cornerPointCount);
}

unsigned int RoundedRectangleView::getCornerPointCount() const
{
    return mRect.getPointCount();
}

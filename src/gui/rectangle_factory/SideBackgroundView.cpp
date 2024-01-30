#include <SideBackgroundView.hpp>
#include <iostream>

SideBackgroundView::SideBackgroundView(Activity *publisher, const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color, const sf::FloatRect &viewRect)
    : RectangleView(dynamic_cast<EventPublisher*>(publisher), size, position, color)
    , sideView(viewRect)
    , scrollSpeed(SIDE_VIEW_SCROLL_SPEED)
    , scrolledDistance(0)
    , publisher(publisher)
    , maxScrollDistance(DEFAULT_MAX_SCROLL_DISTANCE)
{
    sideView.setViewport(sf::FloatRect(0, 0.159, 0.257, 0.841));
    sideView.setCenter(165.f, 400.f);

    setOnMouseWheelScrolled([&](EventListener* listener, const sf::Event &event)
    {
        if (isMouseHovering(sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y)))
        {
            float scrollSpeed = getScrollSpeed();
            move(0.f, scrollSpeed * event.mouseWheelScroll.delta);
        }
    });
}

void SideBackgroundView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!isVisible())
        return;

    states.transform *= getTransform();
    drawCurrent(target, states);
    target.setView(sideView);
    drawChildren(target, states);
    target.setView(target.getDefaultView());
}

void SideBackgroundView::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    RectangleView::drawCurrent(target, states);
}

void SideBackgroundView::move(float x, float y)
{
    if (scrolledDistance + y > maxScrollDistance)
    {
        sideView.move(x, maxScrollDistance - scrolledDistance);
        scrolledDistance = maxScrollDistance;
    }
    else if (scrolledDistance + y < 0)
    {
        sideView.move(x, -scrolledDistance);
        scrolledDistance = 0;
    }
    else if (scrolledDistance + y >= 0 && scrolledDistance + y <= maxScrollDistance)
    {
        sideView.move(x, y);
        scrolledDistance += y;
    }
}

void SideBackgroundView::move(const sf::Vector2f &direction)
{
    move(direction.x, direction.y);
}

void SideBackgroundView::setScrollSpeed(float scrollSpeed)
{
    this->scrollSpeed = scrollSpeed;
}

float SideBackgroundView::getScrollSpeed() const
{
    return scrollSpeed;
}

sf::View& SideBackgroundView::getView()
{
    return sideView;
}

sf::Vector2f& SideBackgroundView::getSideMouseCoords() const
{
    sf::RenderWindow& window = publisher->getActivityManager()->getWindow();
    sf::Vector2f mappedMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), sideView);
    return mappedMousePosition;
}

void SideBackgroundView::setMaxScrollDistance(float maxScrollDistance)
{
    this->maxScrollDistance = maxScrollDistance;
}
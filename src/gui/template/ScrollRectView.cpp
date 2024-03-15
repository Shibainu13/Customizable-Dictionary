#include <ScrollRectView.hpp>

ScrollRectView::ScrollRectView(Activity *publisher, const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color, const sf::FloatRect &viewRect)
    : RectangleView(dynamic_cast<EventPublisher*>(publisher), size, position, color)
    , view(viewRect)
    , scrollSpeed(DEFAULT_SCROLL_SPEED)
    , scrolledDistance(0)
    , publisher(publisher)
    , maxScrollDistance(0)
{
    setViewPort(sf::FloatRect(0, 0, 1, 1));
    setCenter(AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::WINDOW_SIZE));

    setOnMouseWheelScrolled([this](EventListener* listener, const sf::Event& event)
    {
        if (isMouseHovering(sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y)))
        {
            float scrollSpeed = this->getScrollSpeed();
            this->move(0.f, scrollSpeed * event.mouseWheelScroll.delta);
        }
    });
}

void ScrollRectView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!isVisible())
        return;

    states.transform *= getTransform();
    drawCurrent(target, states);
    target.setView(view);
    drawChildren(target, states);
    target.setView(target.getDefaultView());
}

void ScrollRectView::move(float x, float y)
{
    if (scrolledDistance + y > maxScrollDistance)
    {
        view.move(x, maxScrollDistance - scrolledDistance);
        scrolledDistance = maxScrollDistance;
    }
    else if (scrolledDistance + y < 0)
    {
        view.move(x, -scrolledDistance);
        scrolledDistance = 0;
    }
    else if (scrolledDistance + y >= 0 && scrolledDistance + y <= maxScrollDistance)
    {
        view.move(x, y);
        scrolledDistance += y;
    }
}

void ScrollRectView::move(const sf::Vector2f &direction)
{
    move(direction.x, direction.y);
}

void ScrollRectView::moveToTop()
{
    move(0, -scrolledDistance);
}

void ScrollRectView::setScrollSpeed(float scrollSpeed)
{
    this->scrollSpeed = scrollSpeed;
}

float ScrollRectView::getScrollSpeed() const
{
    return scrollSpeed;
}

sf::View& ScrollRectView::getView()
{
    return view;
}

sf::Vector2f& ScrollRectView::getRectMouseCoords() const
{
    sf::RenderWindow& window = publisher->getActivityManager()->getWindow();
    sf::Vector2f mappedMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    return mappedMousePosition;
}

void ScrollRectView::setViewPort(const sf::FloatRect& viewport)
{
    view.setViewport(viewport);
}

void ScrollRectView::setCenter(float x, float y)
{
    view.setCenter(x, y);
}

void ScrollRectView::setCenter(const sf::Vector2f& pos)
{
    view.setCenter(pos);
}

void ScrollRectView::setMaxScrollDistance(float maxScrollDistance)
{
    this->maxScrollDistance = maxScrollDistance;
}

float ScrollRectView::getMaxScrollDistance() const
{
    return maxScrollDistance;
}


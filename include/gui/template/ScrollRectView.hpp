#ifndef SCROLL_RECT_VIEW_HPP
#define SCROLL_RECT_VIEW_HPP

#include <RectangleView.hpp>
#include <Activity.hpp>
#include <AppConfig.hpp>

class ScrollRectView : public RectangleView
{
public:
    typedef std::unique_ptr<ScrollRectView> Ptr;
    static constexpr float DEFAULT_SCROLL_SPEED = 25.f;

public:
    ScrollRectView(Activity *publisher, const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color, const sf::FloatRect &viewRect);

    void move(float x, float y);
    void move(const sf::Vector2f &direction);

    void moveToTop();

    void setScrollSpeed(float scrollSpeed);
    float getScrollSpeed() const;

    sf::View &getView();
    sf::Vector2f &getRectMouseCoords() const;

    void setViewPort(const sf::FloatRect &viewport);
    void setCenter(float x, float y);
    void setCenter(const sf::Vector2f &pos);

    void setMaxScrollDistance(float maxScrollDistance);
    float getMaxScrollDistance() const;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::View view;
    float scrollSpeed;
    float scrolledDistance;
    float maxScrollDistance;
    Activity *publisher;
};

#endif
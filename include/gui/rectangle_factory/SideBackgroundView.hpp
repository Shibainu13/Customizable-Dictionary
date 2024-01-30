#ifndef SIDE_BACKGROUND_VIEW_HPP
#define SIDE_BACKGROUND_VIEW_HPP

#include <RectangleView.hpp>
#include <Activity.hpp>
#include <cmath>

class SideBackgroundView : public RectangleView
{
public:
    typedef std::unique_ptr<SideBackgroundView> Ptr;
    static constexpr float SIDE_VIEW_SCROLL_SPEED = 25.f;
    static constexpr float DEFAULT_MAX_SCROLL_DISTANCE = 600.f;

public:
    SideBackgroundView(Activity *publisher, const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color, const sf::FloatRect &viewRect);

    void move(float x, float y);
    void move(const sf::Vector2f &direction);

    void setScrollSpeed(float scrollSpeed);
    float getScrollSpeed() const;

    sf::View &getView();
    sf::Vector2f &getSideMouseCoords() const;

    void setMaxScrollDistance(float maxScrollDistance);

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::View sideView;
    float scrollSpeed;
    float scrolledDistance;
    float maxScrollDistance;
    Activity *publisher;
};

#endif
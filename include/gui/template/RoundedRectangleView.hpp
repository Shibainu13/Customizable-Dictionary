#ifndef ROUNDED_RECTANGLE_VIEW_HPP
#define ROUNDED_RECTANGLE_VIEW_HPP

#include <RoundedRectangleShape.hpp>
#include <ViewGroup.hpp>
#include <EventListener.hpp>

class RoundedRectangleView : public ViewGroup
{
public:
    typedef std::unique_ptr<RoundedRectangleView> Ptr;

private:
    sf::RoundedRectangleShape mRect;

public:
    RoundedRectangleView(EventPublisher *publisher, float left, float top, float width, float height, float cornersRadius, unsigned int cornerPointCount);
    RoundedRectangleView(EventPublisher *publisher, float left, float top, float width, float height, float cornersRadius, unsigned int cornerPointCount, const sf::Color &color);
    RoundedRectangleView(EventPublisher *publisher, const sf::Vector2f &size, float cornersRadius, unsigned int cornerPointCount, const sf::Vector2f &position);
    RoundedRectangleView(EventPublisher *publisher, const sf::Vector2f &size, float cornersRadius, unsigned int cornerPointCount, const sf::Vector2f &position, const sf::Color &color);

    sf::Vector2f getSize();
    void setSize(const sf::Vector2f &size);
    void setFillColor(sf::Color color);
    bool isMouseHovering(const sf::Vector2f &mousePoint) const;

    sf::FloatRect getGlobalBounds() const;
    void setOutlineThickness(float thickness);
    void setOutineColor(const sf::Color &color);

    void setCornersRadius(float radius);
    float getCornersRadius() const;

    void setCornerPointCount(unsigned int cornerPointCount);
    unsigned int getCornerPointCount() const;

protected:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual bool isOnMouseButtonPressed(const sf::Event &event) const override;
    virtual bool isOnMouseButtonReleased(const sf::Event &event) const override;
};

#endif
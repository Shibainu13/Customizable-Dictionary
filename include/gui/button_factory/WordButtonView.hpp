#ifndef WORD_BUTTON_VIEW_HPP
#define WORD_BUTTON_VIEW_HPP

#include <EventListener.hpp>
#include <Activity.hpp>
#include <ColoredButtonView.hpp>
#include <TextView.hpp>
#include <ScrollRectView.hpp>

class WordButtonView : public ButtonView
{
private:
    enum class ButtonType
    {
        NORMAL,
        HOVERING,
        PRESSED,
        COUNT
    };

public:
    typedef std::unique_ptr<WordButtonView> Ptr;

public:
    WordButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f& size, ScrollRectView *sideView);
    WordButtonView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f& size, const sf::Color* colors, ScrollRectView *sideView);

    void setOnMouseButtonPressed(EventCallback onMouseButtonPressed) override;
    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;
    void setOnMouseMoved(EventCallback onMouseMoved) override;

    void setColors(const sf::Color* colors);

private:
    ScrollRectView *sideView;
    sf::Color buttonColors[3];

protected:
    virtual bool isOnMouseButtonPressed(const sf::Event &event) const override;
    virtual bool isOnMouseButtonReleased(const sf::Event &event) const override;
    virtual bool isOnMouseMoved(const sf::Event &event) const override;
};

#endif

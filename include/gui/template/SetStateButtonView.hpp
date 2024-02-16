#ifndef SET_STATE_BUTTON_VIEW
#define SET_STATE_BUTTON_VIEW

#include <SpriteButtonView.hpp>
#include <Activity.hpp>
#include <EventListener.hpp>

class SetStateButtonView : public ButtonView
{
public:
    typedef std::unique_ptr<SetStateButtonView> Ptr;

public:
    enum class ButtonType
    {
        NORMAL,
        HOVERING,
        PRESSED,
        COUNT
    };

private:
    static constexpr int BORDER_WIDTH = 2.f;

private:
    std::string mTexts[int(ButtonType::COUNT)];
    sf::IntRect mTextureRects[int(ButtonType::COUNT)];

public:
    SetStateButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);

    void setOnMouseButtonPressed(EventCallback onMouseButtonPressed) override;
    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;
    void setOnMouseMoved(EventCallback onMouseMoved) override;

protected:
    virtual bool isOnMouseButtonPressed(const sf::Event &event) const override;
    virtual bool isOnMouseButtonReleased(const sf::Event &event) const override;
    virtual bool isOnMouseMoved(const sf::Event &event) const override;
};

#endif
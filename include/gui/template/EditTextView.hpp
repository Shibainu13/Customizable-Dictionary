#ifndef EDIT_TEXT_VIEW_HPP
#define EDIT_TEXT_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <ViewGroup.hpp>
#include <EventListener.hpp>
#include <AppConfig.hpp>
#include <TextView.hpp>

#include <array>
#include <memory>
#include <iostream>

class EditTextView : public ViewGroup
{
public:
    typedef std::unique_ptr<EditTextView> Ptr;
    static const unsigned int DEFAULT_LINE_LIMIT = 5;

public:
    enum InputType
    {
        TEXT,
        PASSWORD
    };
    enum Alignment
    {
        CENTER,
        LEFT
    };

protected:
    bool mIsFocused;
    bool mWrapEnabled;
    sf::RectangleShape mRect;
    sf::Text mCursor;
    // std::array<sf::Text, DEFAULT_LINE_LIMIT> mTexts;
    // std::array<TextView::Ptr, DEFAULT_LINE_LIMIT> mTexts;
    sf::Text mText;
    std::string mString;
    sf::Time mCursorBlinkTime, mCurrentTime;
    bool mCursorVisible;
    InputType mInputType;
    Alignment alignment;
    sf::Color mFocusBackgroundColor, mUnfocusBackgroundColor;
    int numLines;
    sf::Color mFocusBorderColor, mUnFocusBorderColor;
    float focusThickness, unfocusThickness;
    bool mWrapUp, mDropdown;

public:
    EditTextView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &size);
    EditTextView(EventPublisher *publisher, const sf::Font &font, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size);
    EditTextView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size);
    EditTextView(EventPublisher *publisher, const sf::Font &cursorFont, const sf::Font &font, unsigned int characterSize, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size);

    void setInputType(InputType type);
    void setFocusBackgroundColor(const sf::Color &color);
    void setUnfocusBackgroundColor(const sf::Color &color);
    void setTextColor(const sf::Color &color);
    void setAlignment(Alignment alignment);

    void appendCharacter(char character);
    void removeCharacter();
    void clearText();

    const std::string &getText() const;
    sf::FloatRect getGlobalBounds() const;
    bool isMouseHovering(const sf::Vector2f &mousePoint) const;
    bool isFocused() const;
    void setFocused(bool focused);
    void setWrapEnabled(bool enable);

    void setOnTextEntered(EventCallback onTextEntered) override;
    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;

    int getNumLines() const;
    void setFocusBorder(const sf::Color &color, float thickness);
    void setUnFocusBorder(const sf::Color &color, float thickness);

    bool alertWrapUp() const;
    bool alertDropdown() const;

    void disableAlerts();
    
protected:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual bool isOnMouseButtonPressed(const sf::Event &event) const override;
    virtual bool isOnTextEntered(const sf::Event &event) const override;

protected:
    void setText(const std::string &text);

    virtual void updateTextPosition();
    void updateBackgroundColor();
    virtual void updateCurrent(sf::Time delta) override;

    void setBlinkTime(sf::Time time);
    void resetBlink();

    void setBackgroundColor(const sf::Color &color);
    void setBorderColor(const sf::Color &color, float thickness);
    void updateBorderColor();
};

#endif
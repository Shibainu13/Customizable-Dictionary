#ifndef EDIT_TEXT_ON_SCROLL_VIEW_HPP
#define EDIT_TEXT_ON_SCROLL_VIEW_HPP

#include <EditTextView.hpp>
#include <ScrollRectView.hpp>

class EditTextOnScrollView : public EditTextView
{
public:
    typedef std::unique_ptr<EditTextOnScrollView> Ptr;

public:
    EditTextOnScrollView(EventPublisher *publisher, const sf::Font &font, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, ScrollRectView *rectView);
    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;

protected:
    void updateTextPosition() override;

private:
    ScrollRectView *rectView;
};

#endif
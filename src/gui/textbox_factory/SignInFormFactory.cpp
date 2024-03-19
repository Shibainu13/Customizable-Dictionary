#include <SignInFormFactory.hpp>

EditTextView::Ptr SignInFormFactory::create(Activity *context, const sf::Font &foregroundFont, const std::string &foregroundText, const sf::Font &overTextFont, const std::string &overText, const sf::Vector2f &position)
{
    const sf::Vector2f overTextPos(-23.f, -56.f);
    unsigned int overTextCharacterSize = 16;
    TextView::Ptr overTexts = std::make_unique<TextView>(context, overText, overTextFont, overTextPos, overTextCharacterSize, sf::Color::Black);

    unsigned int foregrounTextCharacterSize = 14;
    const sf::Vector2f foregroundTextPos(0.f, 4.f);
    TextView::Ptr foregroundTexts = std::make_unique<TextView>(context, foregroundText, foregroundFont, foregroundTextPos, foregrounTextCharacterSize, sf::Color(128, 128, 128));
    TextView *foregroundTextPtr = foregroundTexts.get();

    const sf::Vector2f textboxSize(374.f, 19.f);
    EditTextView::Ptr formTextbox = std::make_unique<EditTextView>(context, foregroundFont, "", foregrounTextCharacterSize, position, textboxSize);
    formTextbox->setFocusBackgroundColor(sf::Color::White);
    formTextbox->setUnfocusBackgroundColor(sf::Color::White);
    
    const sf::Vector2f textboxBackgroundSize(420.f, 57.f);
    const sf::Vector2f textboxBackgroundPos(-23.f, -19.f);
    unsigned int backgroundCornerPoint = 4;
    float backgroundRadius = 9.f;
    RoundedRectangleView::Ptr background = std::make_unique<RoundedRectangleView>(context, textboxBackgroundSize, backgroundRadius, backgroundCornerPoint, textboxBackgroundPos, sf::Color::Transparent);
    RoundedRectangleView *backgroundPtr = background.get();
    background->setOutlineThickness(1.f);
    background->setOutineColor(sf::Color::Black);

    formTextbox->setOnMouseButtonReleased([foregroundTextPtr, foregroundText, backgroundPtr](EventListener *listener, const sf::Event &event)
    {
        EditTextView *textbox = dynamic_cast<EditTextView *>(listener);
        if (!textbox->isFocused() && textbox->getText() == "")
        {
            backgroundPtr->setOutineColor(sf::Color::Black);
            foregroundTextPtr->setText(foregroundText);
        }
        else if (textbox->isFocused())
        {
            backgroundPtr->setOutineColor(sf::Color(24, 197, 153));
            foregroundTextPtr->setText("");
        }
        else if (!textbox->isFocused())
            backgroundPtr->setOutineColor(sf::Color::Black);
    });

    formTextbox->attachView(std::move(overTexts));
    formTextbox->attachView(std::move(foregroundTexts));
    formTextbox->attachView(std::move(background));
    return std::move(formTextbox);
}
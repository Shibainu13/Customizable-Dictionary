#include <LastLoginFactory.hpp>

RoundedRectangleView::Ptr LastLoginFactory::create(Activity *context, const sf::Font &mediumFont, const std::string &username, const sf::Font &lightFont, const std::string &lastLogoutTime, const sf::Texture &texture, const sf::Vector2f &position)
{
    const sf::Vector2f profilePos(32.f, 24.f);
    const sf::Vector2f profileSize(76.f, 76.f);
    SpriteView::Ptr profile = std::make_unique<SpriteView>(context, texture, profilePos, profileSize);

    const sf::Vector2f outlineSize(145.f, 164.f);

    const sf::Vector2f usernameTextPos(0.f, 107.f);
    unsigned int usernameCharacterSize = 15;
    TextView::Ptr usernameText = std::make_unique<TextView>(context, username, mediumFont, usernameTextPos, usernameCharacterSize);
    if (usernameText->getGlobalBounds().getSize().x >= outlineSize.x)
    {
        for (int i = 0; i < usernameText->getText().size(); i++)
        {
            if (usernameText->findCharacterPos(i).x >= outlineSize.x - 11.f)
            {
                usernameText->setText(username.substr(0, i - 1) + "...");
                break;
            }
        }
    }
    usernameText->setPosition((outlineSize.x - usernameText->getGlobalBounds().getSize().x) / 2.f, 107.f);

    const sf::Vector2f activeTextPos(0.f, 129.f);
    unsigned int activetTextCharacterSize = 13;
    TextView::Ptr activeText = std::make_unique<TextView>(context, lastLogoutTime, lightFont, activeTextPos, activetTextCharacterSize, sf::Color(173, 173, 173));
    activeText->setPosition((outlineSize.x - activeText->getGlobalBounds().getSize().x) / 2.f, 129.f);

    float outlineCornerRadius = 9.f;
    unsigned int outlineCornerPoints = 4;
    RoundedRectangleView::Ptr outline = std::make_unique<RoundedRectangleView>(context, outlineSize, outlineCornerRadius, outlineCornerPoints, position, sf::Color(239, 248, 255));

    outline->attachView(std::move(profile));
    outline->attachView(std::move(usernameText));
    outline->attachView(std::move(activeText));

    return std::move(outline);
}
#ifndef LAST_LOGIN_FACTORY_HPP
#define LAST_LOGIN_FACTORY_HPP

#include <RoundedRectangleView.hpp>
#include <TextView.hpp>
#include <SpriteView.hpp>
#include <Activity.hpp>

class LastLoginFactory
{
public:
    static RoundedRectangleView::Ptr create(Activity *context, const sf::Font &mediumFont, const std::string &username, const sf::Font &lightFont, const std::string &lastLogoutTime, const sf::Texture &texture, const sf::Vector2f &position);
};

#endif
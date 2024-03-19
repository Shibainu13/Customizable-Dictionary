#ifndef SIGN_IN_FORM_FACTORY
#define SIGN_IN_FORM_FACTORY

#include <EditTextView.hpp>
#include <TextView.hpp>
#include <RoundedRectangleView.hpp>
#include <Activity.hpp>
#include <EventListener.hpp>

class SignInFormFactory
{
public:
    static EditTextView::Ptr create(Activity *context, const sf::Font &foregroundFont, const std::string &foregroundText, const sf::Font &overTextFont, const std::string &overText, const sf::Vector2f &position);
};

#endif
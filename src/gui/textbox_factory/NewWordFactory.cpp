#include <NewWordFactory.hpp>

EditTextView::Ptr NewWordFactory::create(Activity *publisher, const sf::Font &font, const sf::Vector2f &position)
{
    const sf::Vector2f newWordTextSize(278.f, 44.f);
    EditTextView::Ptr newWordText = std::make_unique<EditTextView>(publisher, font, "Enter new word here", position, newWordTextSize);
    newWordText->setFocusBackgroundColor(sf::Color(17, 105, 142));
    newWordText->setUnfocusBackgroundColor(sf::Color(17, 105, 142));
    newWordText->setTextColor(sf::Color(255, 255, 255, 175));

    return std::move(newWordText);
}
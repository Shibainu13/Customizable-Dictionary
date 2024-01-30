#include <SpriteButtonView.hpp>

SpriteButtonView::SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const char *text, unsigned int characterSize, const sf::Vector2f &position)
    : SpriteButtonView(publisher, texture, font, textureRects, (std::string)text, characterSize, position)
{
}

SpriteButtonView::SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position)
    : ButtonView(publisher, texture, font, text, characterSize, position, textureRects[(int)ButtonType::NORMAL])
{
    for (int i = 0; i < (int)ButtonType::COUNT; i++)
    {
        mTexts[i] = text;
        mTextureRects[i] = textureRects[i];
        mBorderColors[i] = sf::Color::Transparent;
    }

    setOnMouseButtonPressed([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseMoved([&](EventListener *listener, const sf::Event &event) {});
}

SpriteButtonView::SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const char *text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size)
    : SpriteButtonView(publisher, texture, font, textureRects, std::string(text), characterSize, position, size)
{
}

SpriteButtonView::SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size)
    : ButtonView(publisher, texture, font, text, characterSize, position, textureRects[(int)ButtonType::NORMAL], size)
{
    for (int i = 0; i < (int)ButtonType::COUNT; i++)
    {
        mTexts[i] = text;
        mTextureRects[i] = textureRects[i];
        mBorderColors[i] = sf::Color::Transparent;
    }

    setOnMouseButtonPressed([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseMoved([&](EventListener *listener, const sf::Event &event) {});
}

SpriteButtonView::SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string *texts, unsigned int characterSize, const sf::Vector2f &position)
    : ButtonView(publisher, texture, font, texts[0], characterSize, position, textureRects[(int)ButtonType::NORMAL])
{
    for (int i = 0; i < (int)ButtonType::COUNT; i++)
    {
        mTexts[i] = texts[i];
        mTextureRects[i] = textureRects[i];
        mBorderColors[i] = sf::Color::Transparent;
    }

    setOnMouseButtonPressed([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseMoved([&](EventListener *listener, const sf::Event &event) {});
}

SpriteButtonView::SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string *texts, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size)
    : ButtonView(publisher, texture, font, texts[0], characterSize, position, textureRects[(int)ButtonType::NORMAL], size)
{
    for (int i = 0; i < (int)ButtonType::COUNT; i++)
    {
        mTexts[i] = texts[i];
        mTextureRects[i] = textureRects[i];
        mBorderColors[i] = sf::Color::Transparent;
    }

    setOnMouseButtonPressed([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseMoved([&](EventListener *listener, const sf::Event &event) {});
}

SpriteButtonView::SpriteButtonView(EventPublisher *publisher, const sf::Texture &texture, const sf::Font &font, const sf::IntRect *textureRects, const std::string &text, unsigned int characterSize, const sf::Vector2f &position, const sf::Vector2f &size, sf::Color *borderColors)
    : ButtonView(publisher, texture, font, text, characterSize, position, textureRects[(int)ButtonType::NORMAL], size, sf::Vector2f(texture.getSize().x, texture.getSize().y))
{
    for (int i = 0; i < (int)ButtonType::COUNT; i++)
    {
        mTexts[i] = text;
        mTextureRects[i] = textureRects[i];
        mBorderColors[i] = borderColors[i];
    }

    setOnMouseButtonPressed([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event) {});
    setOnMouseMoved([&](EventListener *listener, const sf::Event &event) {});
}

void SpriteButtonView::setOnMouseButtonPressed(EventCallback onMouseButtonPressed)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        this->setTextureRect(mTextureRects[(int)ButtonType::PRESSED]);
        this->setBorderColor(mBorderColors[(int)ButtonType::PRESSED], BORDER_WIDTH);
        this->setText(mTexts[(int)ButtonType::PRESSED]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonPressed);
    EventListener::setOnMouseButtonPressed(onEvent);
}

void SpriteButtonView::setOnMouseButtonReleased(EventCallback onMouseButtonReleased)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        this->setTextureRect(mTextureRects[(int)ButtonType::HOVERING]);
        this->setBorderColor(mBorderColors[(int)ButtonType::HOVERING], BORDER_WIDTH);
        this->setText(mTexts[(int)ButtonType::HOVERING]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonReleased);
    EventListener::setOnMouseButtonReleased(onEvent);
}

void SpriteButtonView::setOnMouseMoved(EventCallback onMouseMoved)
{
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener *listener, const sf::Event &event, EventCallback callback)
    {
        if (this->isMouseHovering(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Right) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                this->setTextureRect(mTextureRects[(int)ButtonType::PRESSED]);
                this->setBorderColor(mBorderColors[(int)ButtonType::PRESSED], BORDER_WIDTH);
                this->setText(mTexts[(int)ButtonType::PRESSED]);
            }
            else
            {
                this->setTextureRect(mTextureRects[(int)ButtonType::HOVERING]);
                this->setBorderColor(mBorderColors[(int)ButtonType::HOVERING], BORDER_WIDTH);
                this->setText(mTexts[(int)ButtonType::HOVERING]);
            }
        }
        else
        {
            this->setTextureRect(mTextureRects[(int)ButtonType::NORMAL]);
            this->setBorderColor(mBorderColors[(int)ButtonType::NORMAL], BORDER_WIDTH);
            this->setText(mTexts[(int)ButtonType::NORMAL]);
        }
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseMoved);
    EventListener::setOnMouseMoved(onEvent);
}
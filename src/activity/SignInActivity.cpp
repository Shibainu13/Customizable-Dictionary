#include <SignInActivity.hpp>

//========================================================================================================================//
// Framework init //
//========================================================================================================================//

void SignInActivity::onLoadResource()
{
    mTextureManager.load(TextureID::saly_mark, "res/texture/login/saly.png");
    mTextureManager.load(TextureID::profile, "res/texture/login/profile.png");
    mTextureManager.load(TextureID::shaded_rect, "res/texture/login/profile.png");
    mTextureManager.load(TextureID::x_vec, "res/texture/login/x_vec.png");
    mTextureManager.load(TextureID::app_icon, "res/texture/header/icon.png");

    mFontManager.load(FontID::poppins_light, "res/font/Poppins/Poppins-Light.ttf");
    mFontManager.load(FontID::poppins_medium, "res/font/Poppins/Poppins-Medium.ttf");
    mFontManager.load(FontID::poppins_regular, "res/font/Poppins/Poppins-Regular.ttf");
    mFontManager.load(FontID::poppins_semibold, "res/font/Poppins/Poppins-SemiBold.ttf");
}

void SignInActivity::onCreate()
{
    attachStaticElements();
}

void SignInActivity::onAttach()
{
    // ...
}

void SignInActivity::onPause()
{
    // ...
}

void SignInActivity::onResume()
{
    // ...
}

void SignInActivity::onDestroy()
{
    // ...
}

void SignInActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data)
{
    // ...
}

void SignInActivity::onEvent(const sf::Event &event)
{
    // ...
}

void SignInActivity::onDraw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // ...
}

void SignInActivity::updateCurrent(sf::Time dt)
{
    // ...
}

void SignInActivity::attachStaticElements()
{
    const sf::Vector2f backgroundSize(1280.f, 360.f);
    const sf::Vector2f backgroundPosition(0.f, 0.f);
    RectangleView::Ptr background = std::make_unique<RectangleView>(this, backgroundSize, backgroundPosition, sf::Color(17, 105, 142));

    const sf::Vector2f iconPosition(42.f, 18.f);
    SpriteView::Ptr appIcon = std::make_unique<SpriteView>(this, mTextureManager.get(TextureID::app_icon), iconPosition);

    const sf::Vector2f logoTextPosition(102.f, 28.f);
    unsigned int logoCharacterSize = 20;
    TextView::Ptr logoText = std::make_unique<TextView>(this, "Earthium", mFontManager.get(FontID::poppins_semibold), logoTextPosition, logoCharacterSize, sf::Color::White);

    const sf::Vector2f titlePosition(56.f, 109.f);
    unsigned int titleCharacterSize = 35;
    const std::string titleText = "Sign in to";
    TextView::Ptr title = std::make_unique<TextView>(this, titleText, mFontManager.get(FontID::poppins_semibold), titlePosition, titleCharacterSize, sf::Color::White);

    const sf::Vector2f subtitlePosition(56.f, 154.f);
    unsigned int subtitleCharacterSize = 25;
    const std::string subtitleText = "Earthium Dictionary is simply";
    TextView::Ptr subtitle = std::make_unique<TextView>(this, subtitleText, mFontManager.get(FontID::poppins_light), subtitlePosition, subtitleCharacterSize, sf::Color::White);

    const sf::Vector2f capPosition(52.f, 190.f);
    unsigned int capCharacterSize = 13;
    const std::string capText = " Welcome to Earthium Dictionary, your gateway\n to language exploration. Uncover the depths of\n meaning, let Earthium Dictionary be your guide\n in the realm of words.";
    TextView::Ptr cap = std::make_unique<TextView>(this, capText, mFontManager.get(FontID::poppins_light), capPosition, capCharacterSize, sf::Color::White);

    const sf::Vector2f markPosition(353.f, 6.f);
    SpriteView::Ptr mark = std::make_unique<SpriteView>(this, mTextureManager.get(TextureID::saly_mark), markPosition);

    background->attachView(std::move(appIcon));
    background->attachView(std::move(logoText));
    background->attachView(std::move(title));
    background->attachView(std::move(subtitle));
    background->attachView(std::move(cap));
    background->attachView(std::move(mark));

    attachView(std::move(background));
}
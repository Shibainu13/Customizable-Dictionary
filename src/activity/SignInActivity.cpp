#include <SignInActivity.hpp>

//========================================================================================================================//
// Framework init //
//========================================================================================================================//

void SignInActivity::onLoadResource()
{
    mTextureManager.load(TextureID::saly_mark, "res/texture/login/saly.png");
    mTextureManager.load(TextureID::profile, "res/texture/login/profile.png");
    mTextureManager.load(TextureID::shaded_rect, "res/texture/login/shaded_rect.png");
    mTextureManager.load(TextureID::x_vec, "res/texture/login/x_vec.png");
    mTextureManager.load(TextureID::app_icon, "res/texture/header/icon.png");

    mFontManager.load(FontID::poppins_light, "res/font/Poppins/Poppins-Light.ttf");
    mFontManager.load(FontID::poppins_medium, "res/font/Poppins/Poppins-Medium.ttf");
    mFontManager.load(FontID::poppins_regular, "res/font/Poppins/Poppins-Regular.ttf");
    mFontManager.load(FontID::poppins_semibold, "res/font/Poppins/Poppins-SemiBold.ttf");
    mFontManager.load(FontID::poppins_bold, "res/font/Poppins/Poppins-Bold.ttf");
}

void SignInActivity::onCreate()
{
    attachStaticElements();
    attachSignInBox();
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

    const sf::Vector2f signInBoxPosition(723.f, 68.f);
    SpriteView::Ptr signInBox = std::make_unique<SpriteView>(this, mTextureManager.get(TextureID::shaded_rect), signInBoxPosition);
    signInBoxPtr = signInBox.get();

    background->attachView(std::move(appIcon));
    background->attachView(std::move(logoText));
    background->attachView(std::move(title));
    background->attachView(std::move(subtitle));
    background->attachView(std::move(cap));
    background->attachView(std::move(mark));

    attachView(std::move(background));
    attachView(std::move(signInBox));
}

void SignInActivity::attachSignInBox()
{
    const sf::Vector2f headerTextPos(29.f, 41.f);
    unsigned int headerCharacterSize = 16;
    TextView::Ptr headerText = std::make_unique<TextView>(this, "Welcome to", mFontManager.get(FontID::poppins_medium), headerTextPos, headerCharacterSize);

    const sf::Vector2f headerBoldPos = sf::Vector2f(102.f, -1.f);
    TextView::Ptr headerBold = std::make_unique<TextView>(this, "Earthium", mFontManager.get(FontID::poppins_bold), headerBoldPos, headerCharacterSize, sf::Color(24, 197, 153));
    headerText->attachView(std::move(headerBold));

    const sf::Vector2f titlePos(29.f, 74.f);
    unsigned int titleCharacterSize = 55;
    TextView::Ptr title = std::make_unique<TextView>(this, "Sign in", mFontManager.get(FontID::poppins_medium), titlePos, titleCharacterSize);

    const sf::Vector2f accountStatePos(360.f, 44.f);
    unsigned int accountStateCharacterSize = 13;
    TextView::Ptr accountState = std::make_unique<TextView>(this, "No Account?", mFontManager.get(FontID::poppins_regular), accountStatePos, accountStateCharacterSize);

    const sf::Vector2f signUpButtonPos(358.f, 58.f);
    const sf::Vector2f signUpButtonSize(49.f, 20.f);
    TextButtonView::Ptr signUpButton = LoginHyperTextButtonFactory::create(this, mFontManager.get(FontID::poppins_regular), "Sign up", signUpButtonPos, signUpButtonSize, 
    [&](EventListener *listener, const sf::Event &event)
    {
        // change to sign up view
    });

    const sf::Vector2f forgotPassButtonPos(334.f, 418.f);
    const sf::Vector2f forgotPassButtonSize(108.f, 20.f);
    TextButtonView::Ptr forgotPassButton = LoginHyperTextButtonFactory::create(this, mFontManager.get(FontID::poppins_regular), "Forgot Password", forgotPassButtonPos, forgotPassButtonSize, 
    [&](EventListener *listener, const sf::Event &event)
    {
        // change password
    });

    const sf::Vector2f usernameTextboxPos(52.f, 238.f);
    const std::string usernameOverText = "Enter your username or email address";
    const std::string usernameForegroundText = "Username or email address";
    EditTextView::Ptr usernameTextbox = SignInFormFactory::create(this, mFontManager.get(FontID::poppins_light), usernameForegroundText, mFontManager.get(FontID::poppins_regular), usernameOverText, usernameTextboxPos);
    EditTextView *usernameTextboxPtr = usernameTextbox.get();

    const sf::Vector2f passwordTextboxPos(52.f, 364.f);
    const std::string passwordOverText = "Enter your Password";
    const std::string passwordForegroundText = "Password";
    EditTextView::Ptr passwordTextbox = SignInFormFactory::create(this, mFontManager.get(FontID::poppins_light), passwordForegroundText, mFontManager.get(FontID::poppins_regular), passwordOverText, passwordTextboxPos);
    passwordTextbox->setInputType(EditTextView::InputType::PASSWORD);
    EditTextView *passwordTextboxPtr = passwordTextbox.get();

    const sf::Vector2f errorPos(78.f, 456.f);
    unsigned int errorCharacterSize = 14;
    TextView::Ptr signInError = std::make_unique<TextView>(this, "", mFontManager.get(FontID::poppins_medium), errorPos, errorCharacterSize, sf::Color(216, 104, 114));
    TextView *signInErrorPtr = signInError.get();

    const sf::Vector2f signInButtonPos(29.f, 479.f);
    ColoredButtonView::Ptr signInButton = SignInButtonFactory::create(this, mFontManager.get(FontID::poppins_medium), "Sign in", signInButtonPos, 
    [this, usernameTextboxPtr, passwordTextboxPtr, signInErrorPtr](EventListener *listener, const sf::Event &event)
    {
        std::cout << "input: " << usernameTextboxPtr->getText() << ' ' << passwordTextboxPtr->getText() << std::endl;
        UserRepo &repo = UserRepo::getInstance();
        UserData user = repo.getUserByLogin(usernameTextboxPtr->getText(), passwordTextboxPtr->getText());
        if (user.notAUser())
        {
            std::cout << "Not a user\n";
            signInErrorPtr->setText("Login failed. Username or password incorrect.");
        }
        else
        {
            std::cout << user.getUsername() << ' ' << user.getPassword() << std::endl;
        }
    });

    signInBoxPtr->attachView(std::move(headerText));
    signInBoxPtr->attachView(std::move(title));
    signInBoxPtr->attachView(std::move(accountState));
    signInBoxPtr->attachView(std::move(signUpButton));
    signInBoxPtr->attachView(std::move(forgotPassButton));
    signInBoxPtr->attachView(std::move(usernameTextbox));
    signInBoxPtr->attachView(std::move(passwordTextbox));
    signInBoxPtr->attachView(std::move(signInButton));
    signInBoxPtr->attachView(std::move(signInError));
}
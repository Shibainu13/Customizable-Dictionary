#include <DictionaryActivity.hpp>

//========================================================================================================================//
// Framework init //
//========================================================================================================================//

void DictionaryActivity::onLoadResource()
{
    // header textures
    mTextureManager.load(TextureID::app_icon, "res/texture/header/icon.png");
    mTextureManager.load(TextureID::dictionary_icon, "res/texture/header/dictionary.png");
    mTextureManager.load(TextureID::daily_icon, "res/texture/header/daily.png");
    mTextureManager.load(TextureID::favorite_icon, "res/texture/header/favorite_list.png");
    mTextureManager.load(TextureID::game_icon, "res/texture/header/game.png");
    mTextureManager.load(TextureID::search_icon, "res/texture/header/search_icon.png");
    mTextureManager.load(TextureID::lang_arrow, "res/texture/header/two-sided-arrow.png");
    mTextureManager.load(TextureID::mode_config, "res/texture/header/mode_config.png");
    mTextureManager.load(TextureID::logout, "res/texture/header/logout.png");

    // sidebar textures
    mTextureManager.load(TextureID::edit_dict, "res/texture/sidebar/edit_dict.png");
    mTextureManager.load(TextureID::del_word, "res/texture/sidebar/del_word.png");
    mTextureManager.load(TextureID::remove_word, "res/texture/sidebar/remove_word.png");

    // dictionary view textures
    mTextureManager.load(TextureID::add_defi, "res/texture/def_display/add_defi.png");
    mTextureManager.load(TextureID::edit_defi, "res/texture/def_display/edit_defi.png");
    mTextureManager.load(TextureID::add_fav, "res/texture/def_display/add_fav.png");
    mTextureManager.load(TextureID::confirm, "res/texture/def_display/confirm.png");
    mTextureManager.load(TextureID::cancel, "res/texture/def_display/cancel.png");

    // fonts
    mFontManager.load(FontID::font_awesome, "res/font/font-awesome-5/Font Awesome 5 Free-Solid-900.otf");
    mFontManager.load(FontID::open_sans, "res/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf");
    mFontManager.load(FontID::serif, "res/font/DM_Serif_Text/DMSerifText-Regular.ttf");
    mFontManager.load(FontID::frank_ruhl, "res/font/Frank_Ruhl_Libre_font/FrankRuhlLibre-Medium.ttf");
    mFontManager.load(FontID::dm_sans, "res/font/DM_Sans/DMSans-VariableFont_opsz,wght.ttf");
}

void DictionaryActivity::createDictionaryFromOrigin()
{
    std::string buildMessage;
    for (int i = 0; i < Datasets::ID::Count; i++)
    {
        std::string indexStr = " (" + std::to_string(i) + ")";
        tries[i]->build_Trie_From_Origin(buildMessage);
        std::cout << buildMessage + indexStr << std::endl;
    }
}

void DictionaryActivity::loadDictionary()
{
    std::string loadMessage;
    for (int i = 0; i < Datasets::ID::Count; i++)
    {
        std::string indexStr = " (" + std::to_string(i) + ")";
        tries[i]->Deserialization_DFS(loadMessage);
        std::cout << loadMessage + indexStr << std::endl;
    }
}

void DictionaryActivity::saveDictionary()
{
    std::string saveMessage;
    for (int i = 0; i < Datasets::ID::Count; i++)
    {
        std::string indexStr = " (" + std::to_string(i) + ")";
        tries[i]->Serialization_DFS(saveMessage);
        std::cout << saveMessage + indexStr << std::endl;
    }
}

void DictionaryActivity::onCreate()
{
    tries[Datasets::ID::Eng_Eng] = new Trie(Datasets::ID::Eng_Eng);
    tries[Datasets::ID::Eng_Viet] = new Trie(Datasets::ID::Eng_Viet);
    tries[Datasets::ID::Viet_Eng] = new Trie(Datasets::ID::Viet_Eng);
    tries[Datasets::ID::Emoji] = new Trie(Datasets::ID::Emoji);
    currentTrie = tries[Datasets::ID::Eng_Eng];
    currentMode = (int)DictionaryMode::WORD_TO_DEF;
    delFlag = false;
    removeFlag = false;
    defiState = true;
    prevDefiState = true;

    createDictionaryFromOrigin();

    getHistory();
    getRandomWords(DEFAULT_RANDOM_QUANTITY);
    getFavorites();

    createHeader();
    createSidebar();
    createDefinitionView();
}

void DictionaryActivity::onAttach()
{
    // ...
}

void DictionaryActivity::onPause()
{
    // ...
}

void DictionaryActivity::onResume()
{
    // ...
}

void DictionaryActivity::onDestroy()
{
    for (int i = 0; i < Datasets::ID::Count; i++)
        delete tries[i];

    // serialize tries
}

void DictionaryActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data)
{
    // ...
}

void DictionaryActivity::onEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed && !isSideButtonsHovering(event))
        removeMarks();
}

void DictionaryActivity::onDraw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // ...
}

void DictionaryActivity::updateCurrent(sf::Time dt)
{
    if (delFlag && wordFlagged != "")
    {
        std::string message;
        currentTrie->remove_Word_FromTrie(wordFlagged, message);
        removeFromHistory(wordFlagged);
        removeMarks();
        wordFlagged = "";
        delFlag = false;
    }
    else if (removeFlag && wordFlagged != "")
    {
        removeFromFavorites(wordFlagged);
        removeMarks();
        wordFlagged = "";
        removeFlag = false;
    }
    if (prevDefiState != defiState)
        setDefiState(!defiState);
}

//========================================================================================================================//
// Header //
//========================================================================================================================//

void DictionaryActivity::createHeader()
{
    sf::Vector2f headerSize(1280, 70);
    sf::Vector2f headerPosition(0, 0);
    RectangleView::Ptr header = std::make_unique<RectangleView>(this, headerSize, headerPosition, sf::Color(25, 69, 107));

    sf::Vector2f iconPosition(15, 9);
    sf::Vector2f iconSize(50, 50);
    SpriteView::Ptr appIcon = std::make_unique<SpriteView>(this, mTextureManager.get(TextureID::app_icon), iconPosition, iconSize);

    sf::Vector2f separatorSize(3, 70);
    sf::Vector2f separatorPosition(79, 0);
    RectangleView::Ptr separator = std::make_unique<RectangleView>(this, separatorSize, separatorPosition, sf::Color::White);

    sf::Vector2f dictionaryButtonPosition(94, 0);
    ColoredButtonView::Ptr dictionaryButton = DictionaryButtonFactory::create(this, mTextureManager.get(TextureID::dictionary_icon), mFontManager.get(FontID::font_awesome), dictionaryButtonPosition,
                                                                              [&](EventListener *listener, const sf::Event &event)
                                                                              {
                                                                                  setSidebarState(SidebarState::HISTORY);
                                                                                  removeMarks();
                                                                                  updateSideButtons(historyWords);
                                                                              });

    sf::Vector2f dailyButtonPosition(193, 0);
    ColoredButtonView::Ptr dailyButton = DailyButtonFactory::create(this, mTextureManager.get(TextureID::daily_icon), mFontManager.get(FontID::font_awesome), dailyButtonPosition,
                                                                    [&](EventListener *listener, const sf::Event &event)
                                                                    {
                                                                        setSidebarState(SidebarState::DAILY);
                                                                        removeMarks();
                                                                        switch (getCurrentDataset())
                                                                        {
                                                                        case Datasets::Eng_Eng:
                                                                            updateSideButtons(dailyWords[Datasets::ID::Eng_Eng]);
                                                                            break;

                                                                        case Datasets::Eng_Viet:
                                                                            updateSideButtons(dailyWords[Datasets::ID::Eng_Viet]);
                                                                            break;

                                                                        case Datasets::Viet_Eng:
                                                                            updateSideButtons(dailyWords[Datasets::ID::Viet_Eng]);
                                                                            break;

                                                                        case Datasets::Emoji:
                                                                            updateSideButtons(dailyWords[Datasets::ID::Emoji]);
                                                                            break;
                                                                        }
                                                                    });

    sf::Vector2f favButtonPosition(292, 0);
    ColoredButtonView::Ptr favButton = FavButtonFactory::create(this, mTextureManager.get(TextureID::favorite_icon), mFontManager.get(FontID::font_awesome), favButtonPosition,
                                                                [&](EventListener *listener, const sf::Event &event)
                                                                {
                                                                    setSidebarState(SidebarState::FAVORITE);
                                                                    removeMarks();
                                                                    updateSideButtons(favWords);
                                                                });

    sf::Vector2f gameButtonPosition(391, 0);
    ColoredButtonView::Ptr gameButton = GameButtonFactory::create(this, mTextureManager.get(TextureID::game_icon), mFontManager.get(FontID::font_awesome), gameButtonPosition,
                                                                  [this](EventListener *listener, const sf::Event &event)
                                                                  {
                                                                      // start game activity
                                                                  });

    ColoredButtonView::Ptr setLangButton = createSetLangButton();

    RectangleView::Ptr searchbar = createSearchbar();

    sf::Vector2f logOutButtonPosition(1205, 12);
    SpriteButtonView::Ptr logOutButton = LogOutButtonFactory::create(this, mTextureManager.get(TextureID::logout), mFontManager.get(FontID::font_awesome), logOutButtonPosition,
                                                                     [this](EventListener *listener, const sf::Event &event)
                                                                     {
                                                                         // log out
                                                                     });

    header->attachView(std::move(appIcon));
    header->attachView(std::move(separator));
    header->attachView(std::move(dictionaryButton));
    header->attachView(std::move(dailyButton));
    header->attachView(std::move(favButton));
    header->attachView(std::move(gameButton));
    header->attachView(std::move(logOutButton));
    header->attachView(std::move(setLangButton));
    header->attachView(std::move(searchbar));

    attachView(std::move(header));
}

RectangleView::Ptr DictionaryActivity::createSearchbar()
{
    sf::Vector2f searchRectPosition(705, 15);
    sf::Vector2f searchRectSize(475, 40);
    RectangleView::Ptr searchbarBackground = std::make_unique<RectangleView>(this, searchRectSize, searchRectPosition, sf::Color(245, 245, 245));
    searchbarBackground->setOutlineThickness(2);
    searchbarBackground->setOutineColor(sf::Color::Black);

    int characterSize = 20;
    sf::Vector2f backgroundTextRelativePosition(0, 4);
    TextView::Ptr backgroundText = std::make_unique<TextView>(this, ModeBackgroundTexts[currentMode], mFontManager.get(FontID::dm_sans), backgroundTextRelativePosition, characterSize, sf::Color(0, 0, 0, 100));
    TextView *backgroundTextPtr = backgroundText.get();

    sf::Vector2f searchbarRelativePosition(49, 9);
    EditTextView::Ptr searchbar = SearchBarFactory::create(
        this, mFontManager.get(FontID::serif), mFontManager.get(FontID::dm_sans), searchbarRelativePosition,
        [&](EventListener *listener, const sf::Event &event) // on text entered
        {
            EditTextView *textbox = dynamic_cast<EditTextView *>(listener);
            std::string currentString = textbox->getText();
            std::vector<std::string> suggestions = getSuggestions(currentString);
            updateSuggestButtons(suggestions);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // enter
            {
                if (textbox->getText() == "")
                    backgroundTextPtr->setText(ModeBackgroundTexts[this->getCurrentMode()]);
                else if (textbox->getText() != "" && suggestButtons.size() == 1)
                    addHistory(textbox->getText());

                emptySuggestButtons();
            }

            // defi view when press enter
        },
        [this, backgroundTextPtr](EventListener *listener, const sf::Event &event) // on mouse released
        {
            EditTextView *textbox = dynamic_cast<EditTextView *>(listener);
            if (!textbox->isFocused() && textbox->getText() != "" && !this->isSuggestButtonsHovering(event))
                this->emptySuggestButtons();

            else if (!textbox->isFocused() && textbox->getText() == "" && !this->isSuggestButtonsHovering(event))
            {
                this->emptySuggestButtons();
                backgroundTextPtr->setText(ModeBackgroundTexts[this->getCurrentMode()]);
            }

            else if (textbox->isFocused())
                backgroundTextPtr->setText("");
        });
    EditTextView *searchbarPtr = searchbar.get();

    sf::Vector2f searchIconRelativePosition(9, 6);
    sf::Vector2f searchIconSize(32, 32);
    SpriteView::Ptr searchIcon = std::make_unique<SpriteView>(this, mTextureManager.get(TextureID::search_icon), searchIconRelativePosition, searchIconSize);

    sf::Vector2f modeConfigRelativePosition(432, 3);
    SpriteButtonView::Ptr modeConfigButton = ModeButtonFactory::create(this, mTextureManager.get(TextureID::mode_config), mFontManager.get(FontID::serif), modeConfigRelativePosition);
    modeConfigButton->setOnMouseButtonReleased([this, backgroundTextPtr, searchbarPtr](EventListener *listener, const sf::Event &event)
                                               {
        this->toggleMode();
        searchbarPtr->clearText();
        backgroundTextPtr->setText(ModeBackgroundTexts[this->getCurrentMode()]); });

    searchbar->attachView(std::move(backgroundText));
    searchbarBackground->attachView(std::move(searchbar));
    searchbarBackground->attachView(std::move(searchIcon));
    searchbarBackground->attachView(std::move(modeConfigButton));
    return std::move(searchbarBackground);
}

bool DictionaryActivity::isSuggestButtonsHovering(const sf::Event &event)
{
    for (auto &button : suggestButtons)
        if (button->isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            return true;
    return false;
}

void DictionaryActivity::toggleMode()
{
    currentMode = !currentMode;
}

bool DictionaryActivity::getCurrentMode() const
{
    return currentMode;
}

ColoredButtonView::Ptr DictionaryActivity::createSetLangButton()
{
    constexpr float HALF_BUTTON_WIDTH = 100.f;
    constexpr float HALF_SPRITE_WIDTH = 25.f;

    int characterSize = 30;
    TextView::Ptr firstLang = std::make_unique<TextView>(this, "Eng", mFontManager.get(FontID::serif), sf::Vector2f(), characterSize, sf::Color::White);
    TextView *firstLangPtr = firstLang.get();
    TextView::Ptr secondLang = std::make_unique<TextView>(this, "Eng", mFontManager.get(FontID::serif), sf::Vector2f(), characterSize, sf::Color::White);
    TextView *secondLangPtr = secondLang.get();

    firstLangPtr->setPosition(sf::Vector2f((HALF_BUTTON_WIDTH - HALF_SPRITE_WIDTH - firstLangPtr->getGlobalBounds().getSize().x) / 2.f, 23.f));
    secondLangPtr->setPosition(sf::Vector2f(HALF_BUTTON_WIDTH + HALF_SPRITE_WIDTH + (HALF_BUTTON_WIDTH - HALF_SPRITE_WIDTH - secondLangPtr->getGlobalBounds().getSize().x) / 2.f, 23.f));

    sf::Vector2f setLangButtonPosition(490, 0);
    ColoredButtonView::Ptr setLangButton = SetLangButtonFactory::create(this, mTextureManager.get(TextureID::lang_arrow), mFontManager.get(FontID::serif), setLangButtonPosition,
                                                                        [this, firstLangPtr, secondLangPtr](EventListener *listener, const sf::Event &event)
                                                                        {
                                                                            this->toggleDataset();
                                                                            switch (this->getCurrentDataset())
                                                                            {
                                                                            case Datasets::ID::Eng_Eng:
                                                                                firstLangPtr->setText("Eng");
                                                                                secondLangPtr->setText("Eng");
                                                                                break;

                                                                            case Datasets::ID::Eng_Viet:
                                                                                firstLangPtr->setText("Eng");
                                                                                secondLangPtr->setText("Vie");
                                                                                break;

                                                                            case Datasets::ID::Viet_Eng:
                                                                                firstLangPtr->setText("Vie");
                                                                                secondLangPtr->setText("Eng");
                                                                                break;

                                                                            case Datasets::ID::Emoji:
                                                                                firstLangPtr->setText("Emo");
                                                                                secondLangPtr->setText("Eng");
                                                                                break;

                                                                            default:
                                                                                throw std::runtime_error("Dataset not exist.");
                                                                            }
                                                                            firstLangPtr->setPosition(sf::Vector2f((HALF_BUTTON_WIDTH - HALF_SPRITE_WIDTH - firstLangPtr->getGlobalBounds().getSize().x) / 2.f, 23.f));
                                                                            secondLangPtr->setPosition(sf::Vector2f(HALF_BUTTON_WIDTH + HALF_SPRITE_WIDTH + (HALF_BUTTON_WIDTH - HALF_SPRITE_WIDTH - secondLangPtr->getGlobalBounds().getSize().x) / 2.f, 23.f));
                                                                        });

    setLangButton->attachView(std::move(firstLang));
    setLangButton->attachView(std::move(secondLang));
    return std::move(setLangButton);
}

Datasets::ID DictionaryActivity::getCurrentDataset() const
{
    return currentTrie->getCurrentDataset();
}

void DictionaryActivity::toggleDataset()
{
    int i = (int)getCurrentDataset() + 1;
    currentTrie = tries[i % (int)Datasets::ID::Count];
    getHistory();
    getRandomWords(DEFAULT_RANDOM_QUANTITY);
    getFavorites();
    switch (sidebarState)
    {
    case SidebarState::HISTORY:
        updateSideButtons(historyWords);
        break;

    case SidebarState::DAILY:
        switch (getCurrentDataset())
        {
        case Datasets::Eng_Eng:
            updateSideButtons(dailyWords[Datasets::ID::Eng_Eng]);
            break;

        case Datasets::Eng_Viet:
            updateSideButtons(dailyWords[Datasets::ID::Eng_Viet]);
            break;

        case Datasets::Viet_Eng:
            updateSideButtons(dailyWords[Datasets::ID::Viet_Eng]);
            break;

        case Datasets::Emoji:
            updateSideButtons(dailyWords[Datasets::ID::Emoji]);
            break;
        }
        break;

    case SidebarState::FAVORITE:
        updateSideButtons(favWords);
        break;
    }
}

std::vector<std::string> DictionaryActivity::getSuggestions(std::string &subWord)
{
    std::vector<std::string> suggestions;
    if (subWord != "" && currentMode == DictionaryMode::WORD_TO_DEF)
        currentTrie->searchForAWord_withSuggestion(subWord, suggestions);
    else if (subWord != "" && currentMode == DictionaryMode::DEF_TO_WORD)
        currentTrie->findWordFromSubDefi(subWord, suggestions);
    return suggestions;
}

void DictionaryActivity::updateSuggestButtons(std::vector<std::string> &suggestions)
{
    emptySuggestButtons();

    if (suggestions.size() == 0)
        return;

    sf::Vector2f buttonPosition(707.f, 60.f);
    const float buttonSpacing = 40.f;
    const sf::Vector2f textRelativePos(49, 9);
    int numberOfSuggestions = (suggestions.size() < MAX_SUGGESTIONS) ? suggestions.size() : MAX_SUGGESTIONS;

    for (int i = 0; i < numberOfSuggestions; i++)
    {
        ColoredButtonView::Ptr buttonPtr = SuggestButtonFactory::create(this, mFontManager.get(FontID::dm_sans), "", buttonPosition,
                                                                        [this](EventListener *listener, const sf::Event &event)
                                                                        {
                                                                            ColoredButtonView *button = dynamic_cast<ColoredButtonView *>(listener);
                                                                            this->addHistory(button->getText());
                                                                            this->displayDefi(button->getText());
                                                                        });
        buttonPtr->setText(suggestions.at(i), textRelativePos);
        suggestButtons.push_back(buttonPtr.get());
        attachView(std::move(buttonPtr));
        buttonPosition = sf::Vector2f(buttonPosition.x, buttonPosition.y + buttonSpacing);
    }
}

void DictionaryActivity::emptySuggestButtons()
{
    while (!suggestButtons.empty())
    {
        ColoredButtonView *button = suggestButtons.back();
        suggestButtons.pop_back();
        detachView(*button);
    }
}

//========================================================================================================================//
// Sidebar //
//========================================================================================================================//

void DictionaryActivity::createSidebar()
{
    sidebarState = SidebarState::HISTORY;
    sideButtonMark = SideButtonMark::NONE;
    const sf::Vector2f backgroundPosition(0, 70);
    ScrollRectView::Ptr background = SideViewFactory::create(this, backgroundPosition);
    sideViewBackground = background.get();

    const sf::Vector2f editButtonPosition(290, 83);
    SpriteButtonView::Ptr editButton = EditDictButtonFactory::create(this, mTextureManager.get(TextureID::edit_dict), mFontManager.get(FontID::font_awesome), editButtonPosition,
                                                                     [&](EventListener *listener, const sf::Event &event)
                                                                     {
                                                                         switch (sidebarState)
                                                                         {
                                                                         case SidebarState::HISTORY:
                                                                             markSideButton(SideButtonMark::DELETE);
                                                                             break;

                                                                         case SidebarState::DAILY:
                                                                             markSideButton(SideButtonMark::DELETE);
                                                                             break;

                                                                         case SidebarState::FAVORITE:
                                                                             markSideButton(SideButtonMark::REMOVE);
                                                                             break;

                                                                         default:
                                                                             markSideButton(SideButtonMark::NONE);
                                                                             break;
                                                                         }
                                                                     });

    updateSideButtons(historyWords);

    attachView(std::move(background));
    attachView(std::move(editButton));
}

bool DictionaryActivity::isSideButtonsHovering(const sf::Event &event)
{
    for (auto &button : sideWordButtons)
        if (button->getGlobalBounds().contains(sideViewBackground->getRectMouseCoords()))
            return true;
    return false;
}

void DictionaryActivity::setSidebarState(SidebarState state)
{
    sidebarState = state;
}

void DictionaryActivity::adjustSideViewScroll()
{
    if (sideWordButtons.size() <= DEFAULT_RANDOM_QUANTITY)
    {
        sideViewBackground->setMaxScrollDistance(0.f);
        return;
    }
    float buttonGap = 60.f;
    float scrollDistance = buttonGap * (sideWordButtons.size() - DEFAULT_RANDOM_QUANTITY);
    sideViewBackground->setMaxScrollDistance(scrollDistance);
}

void DictionaryActivity::getHistory()
{
    std::string message;
    currentTrie->takeHistory(historyWords, message);
    if (message == "Error opening file !")
        std::cerr << message << std::endl;

    if (historyWords.size() < DEFAULT_HISTORY_QUANTITY)
    {
        std::vector<std::string> startupWords = currentTrie->take_First_K_Word(DEFAULT_HISTORY_QUANTITY - historyWords.size());
        historyWords.insert(historyWords.end(), startupWords.begin(), startupWords.end());
        std::cout << historyWords.at(0) << std::endl;
    }
    else if (historyWords.size() > DEFAULT_HISTORY_QUANTITY)
        historyWords.erase(historyWords.begin() + DEFAULT_HISTORY_QUANTITY - 1, historyWords.end() - 1);
}

void DictionaryActivity::addHistory(const std::string &word)
{
    if (historyWords.at(0) == word)
        return;

    std::string message;
    removeFromHistory(word);
    currentTrie->addToHistory(word, message);
    if (message == "Error opening file !")
        std::cerr << message << std::endl;

    historyWords.pop_back();
    historyWords.insert(historyWords.begin(), word);

    if (sidebarState == SidebarState::HISTORY)
        updateSideButtons(historyWords);
}

void DictionaryActivity::removeFromHistory(const std::string &word)
{
    std::string message;
    currentTrie->removeFromHistory(word, message);
    if (message == "Error opening file !")
        std::cerr << message << std::endl;

    std::cout << word << " deleted.\n";
    getHistory();
    if (sidebarState == SidebarState::HISTORY)
        updateSideButtons(historyWords);
}

void DictionaryActivity::emptySideButtons()
{
    while (!sideWordButtons.empty())
    {
        ButtonView *button = sideWordButtons.back();
        sideWordButtons.pop_back();
        sideViewBackground->detachView(*button);
    }
}

void DictionaryActivity::updateSideButtons(std::vector<std::string> &sideButtons)
{
    emptySideButtons();
    const sf::Vector2f firstButtonPosition(15, 0);
    const sf::Vector2f buttonSpacing(0, 10);
    const sf::Vector2f wordButtonSize(300, 50);

    for (int i = 0; auto &word : sideButtons)
    {
        sf::Vector2f buttonPosition = firstButtonPosition + sf::Vector2f(buttonSpacing.x, i * (buttonSpacing.y + wordButtonSize.y));
        WordButtonView::Ptr wordButtonView = std::make_unique<WordButtonView>(this, mFontManager.get(FontID::frank_ruhl), word, buttonPosition, wordButtonSize, sideViewBackground);
        wordButtonView->setOnMouseButtonReleased([&](EventListener *listener, const sf::Event &event)
                                                 {
            WordButtonView* button = dynamic_cast<WordButtonView*>(listener);
            std::cout << button->getText() << std::endl;
            std::string message;
            switch (sideButtonMark)
            {
            case SideButtonMark::DELETE:
                delFlag = true;
                wordFlagged = word;
                return;
            
            case SideButtonMark::REMOVE:
                removeFlag = true;
                wordFlagged = word;
                return;
            
            case SideButtonMark::NONE:
                displayDefi(word);
                return;
        } });
        sideWordButtons.push_back(wordButtonView.get());
        sideViewBackground->attachView(std::move(wordButtonView));
        i++;
    }
    adjustSideViewScroll();
}

void DictionaryActivity::getRandomWords(unsigned int quantity)
{
    for (int i = 0; i < Datasets::ID::Count; i++)
    {
        for (int j = 0; j < quantity; j++)
        {
            std::string word = tries[i]->getRandomWord();
            dailyWords[i].push_back(word);
        }
    }
    std::cout << "Daily fetched.\n";
}

void DictionaryActivity::getFavorites()
{
    std::string message;
    currentTrie->viewFavoriteList(favWords, message);
    if (message == "File not found\n")
        std::cerr << message << std::endl;
    else
        std::cout << "Favorites fetched.\n";
}

void DictionaryActivity::addFavorites(const std::string &word)
{
    auto found = std::find(favWords.begin(), favWords.end(), word);
    if (found != favWords.end())
    {
        std::cerr << word << " already exists in favorites.\n";
        return;
    }
    std::string message;
    currentTrie->addToFavoriteList(word, message);
    std::cout << message << std::endl;

    favWords.insert(favWords.begin(), word);
    if (sidebarState == SidebarState::FAVORITE)
        updateSideButtons(favWords);
}

void DictionaryActivity::removeFromFavorites(const std::string &word)
{
    std::string message;
    currentTrie->removeAWordFromFavoriteList(word, message);
    std::cerr << word << ' ' << message << std::endl;
    getFavorites();
    if (sidebarState == SidebarState::FAVORITE)
        updateSideButtons(favWords);
}

void DictionaryActivity::markSideButton(SideButtonMark mark)
{
    if (mark == sideButtonMark)
        return;
    else
        sideButtonMark = mark;
    if (mark == SideButtonMark::NONE)
    {
        removeMarks();
        return;
    }
    const sf::Texture &texture = (mark == SideButtonMark::REMOVE) ? mTextureManager.get(TextureID::remove_word) : mTextureManager.get(TextureID::del_word);
    sf::Vector2f markPosition(282.f, 14.f);
    const sf::Vector2f markSize(22.f, 22.f);
    for (auto &sideButton : sideWordButtons)
    {
        SpriteView::Ptr delMark = std::make_unique<SpriteView>(this, texture, markPosition, markSize, sf::IntRect(0, 0, 22, 22));
        sideButtonMarks.push_back(delMark.get());
        sideViewBackground->attachView(std::move(delMark));
        markPosition += sf::Vector2f(0, 60.f);
    }
}

void DictionaryActivity::removeMarks()
{
    while (!sideButtonMarks.empty())
    {
        SpriteView *mark = sideButtonMarks.back();
        sideButtonMarks.pop_back();
        sideViewBackground->detachView(*mark);
    }
    sideButtonMark = SideButtonMark::NONE;
}

//========================================================================================================================//
// Definition View //
//========================================================================================================================//

void DictionaryActivity::createDefinitionView()
{
    const sf::Vector2f defiHeaderSize(950.f, 152.f);
    const sf::Vector2f defiHeaderPos(330.f, 70.f);
    RectangleView::Ptr defiHeader = std::make_unique<RectangleView>(this, defiHeaderSize, defiHeaderPos, sf::Color(17, 105, 142));
    defiHeaderPtr = defiHeader.get();

    const sf::Vector2f defiFooterSize(950.f, 40.f);
    const sf::Vector2f defiFooterPos(330.f, 680.f);
    RectangleView::Ptr defiFooter = std::make_unique<RectangleView>(this, defiFooterSize, defiFooterPos, sf::Color(17, 105, 142));

    const sf::Vector2f defiViewPos(330.f, 222.f);
    ScrollRectView::Ptr defiView = DefiViewFactory::create(this, defiViewPos);
    defiViewBackground = defiView.get();

    attachView(std::move(defiView));
    attachView(std::move(defiHeader));
    attachView(std::move(defiFooter));

    // attachEditComponents();
    attachDefiComponents();
    // displayDefi("halloo");
}

void DictionaryActivity::displayDefi(const std::string &word)
{
    defiViewBackground->moveToTop();
    std::vector<std::string> defiLists;
    if (currentTrie->findWordInTrie(word, defiLists))
    {
        defiViewBackground->detachAllViews();
        displayHeaderText(word);
        split_Definition(defiLists, currentDefinition);
    }
    else
    {
        std::cout << word << " not found.\n";
        return;
    }

    if (currentTrie->getCurrentDataset() == Datasets::ID::Eng_Eng)
        displayEngEngDefi();
    else
        displayOtherDefi();
    auto found = std::find(favWords.begin(), favWords.end(), word);
    if (found != favWords.end())
        addFavButtonPtr->setState(true);
    else
        addFavButtonPtr->setState(false);
}

void DictionaryActivity::displayHeaderText(const std::string &word)
{
    if (displayTextPtr)
        defiHeaderPtr->detachView(*displayTextPtr);
    TextView::Ptr displayText = std::make_unique<TextView>(this, word, mFontManager.get(FontID::open_sans));
    displayTextPtr = displayText.get();
    displayText->setCharacterSize(35);
    displayText->setPosition(defiHeaderPtr->getGlobalBounds().getSize().x / 2.f - displayText->getGlobalBounds().getSize().x / 2.f, 28.f);
    displayText->setFillColor(sf::Color::White);
    defiHeaderPtr->attachView(std::move(displayText));
}

void DictionaryActivity::displayEngEngDefi()
{
    sf::Vector2f textPosition(25.f, 28.f);
    std::string prevType = "";
    float scrollIndex = 0;
    for (int i = 1; auto &pair : currentDefinition)
    {
        if (pair.first != prevType)
        {
            TextView::Ptr wordType = std::make_unique<TextView>(this, pair.first, mFontManager.get(FontID::open_sans), textPosition, 30, sf::Color(17, 105, 142));
            prevType = pair.first;
            defiViewBackground->attachView(std::move(wordType));
            textPosition += sf::Vector2f(0.f, 50.f);
            i = 1;
            ++scrollIndex;
            defiViewAttachType.push_back(DefiViewType::WORD_TYPE);
        }
        TextView::Ptr defi = std::make_unique<TextView>(this, std::to_string(i) + "   :  " + pair.second, mFontManager.get(FontID::open_sans), textPosition, 20, sf::Color::Black);
        if (defi->getGlobalBounds().getSize().x > 890.f)
        {
            unsigned int spaceIndex = 0;
            for (int i = 0; i < defi->getText().size(); i++)
            {
                if (defi->getText()[i] == ' ')
                    spaceIndex = i;
                if (defi->findCharacterPos(i).x > 890.f)
                {
                    sf::String str;
                    str += defi->getText();
                    str.erase(spaceIndex);
                    str.insert(spaceIndex, "\n");
                    defi->setText(str);
                    textPosition += sf::Vector2f(0.f, 20.f);
                    scrollIndex += 0.4;
                }
            }
        }
        ++scrollIndex;
        defiViewBackground->attachView(std::move(defi));
        textPosition += sf::Vector2f(0.f, 50.f);
        ++i;
        defiViewAttachType.push_back(DefiViewType::DEFINITION);
    }
    if (scrollIndex > 7)
        defiViewBackground->setMaxScrollDistance((scrollIndex - 7) * 50.f);
    else
        defiViewBackground->setMaxScrollDistance(0.f);
    defiTextPosition = textPosition;
}

void DictionaryActivity::displayOtherDefi()
{
    sf::Vector2f textPosition(25.f, 28.f);
    std::string prevType = "";
    float scrollIndex = 0;
    for (int i = 1; auto &pair : currentDefinition)
    {
        TextView::Ptr defi = std::make_unique<TextView>(this, std::to_string(i) + "   :  " + pair.first, mFontManager.get(FontID::open_sans), textPosition, 20, sf::Color::Black);
        if (defi->getGlobalBounds().getSize().x > 890.f)
        {
            unsigned int spaceIndex = 0;
            for (int i = 0; i < defi->getText().size(); i++)
            {
                if (defi->getText()[i] == ' ')
                    spaceIndex = i;
                if (defi->findCharacterPos(i).x > 890.f)
                {
                    sf::String str;
                    str += defi->getText();
                    str.erase(spaceIndex);
                    str.insert(spaceIndex, "\n");
                    defi->setText(str);
                    textPosition += sf::Vector2f(0.f, 20.f);
                    scrollIndex += 0.4;
                }
            }
        }
        ++scrollIndex;
        defiViewBackground->attachView(std::move(defi));
        textPosition += sf::Vector2f(0.f, 50.f);
        ++i;
        defiViewAttachType.push_back(DefiViewType::DEFINITION);
    }
    if (scrollIndex > 7)
        defiViewBackground->setMaxScrollDistance((scrollIndex - 7) * 50.f);
    else
        defiViewBackground->setMaxScrollDistance(0.f);
    defiTextPosition = textPosition;
}

void DictionaryActivity::attachEditComponents()
{
    const sf::Vector2f newWordTextBoxPos(185.f, 35.f);
    EditTextView::Ptr newWordTextBox = NewWordFactory::create(this, mFontManager.get(FontID::open_sans), newWordTextBoxPos);
    newWordTextboxPtr = newWordTextBox.get();

    const sf::Vector2f addWordTypePos(30.f, 28.f);
    WordButtonView::Ptr addWordTypeButton = NewDefiButtonFactory::create(this, mFontManager.get(FontID::open_sans), "+ Add word type", addWordTypePos, defiViewBackground,
    [&](EventListener *listener, const sf::Event &event)
    {
        attachWordTypeTextbox();
    });
    addWordTypeButtonPtr = addWordTypeButton.get();
    defiViewAttachType.push_back(DefiViewType::BUTTON);

    const sf::Vector2f addDefiLinePos(0.f, 54.f);
    WordButtonView::Ptr addDefLineButton = NewDefiButtonFactory::create(this, mFontManager.get(FontID::open_sans), "+ Add definition", addDefiLinePos, defiViewBackground,
    [&](EventListener *listener, const sf::Event &event)
    {
        attachDefiTextbox();
    });
    addDefiLineButtonPtr = addDefLineButton.get();
    addWordTypeButton->attachView(std::move(addDefLineButton));

    const sf::Vector2f confirmPos(1210.f, 620.f);
    SpriteButtonView::Ptr confirmButton = ModDefButtonFactory::create(this, mTextureManager.get(TextureID::confirm), mFontManager.get(FontID::open_sans), confirmPos,
    [&](EventListener *listener, const sf::Event &event)
    {
        std::cout << "New word: " << newWordTextboxPtr->getText() << std::endl;
        for (int i = 0; i < defiViewBackground->getViews().size(); i++)
        {
            EditTextOnScrollView *textbox = dynamic_cast<EditTextOnScrollView *>(defiViewBackground->getViews().at(i).get());
            if (textbox)
                textbox->setFocused(false);
            if (defiViewAttachType.at(i) == DefiViewType::WORD_TYPE && textbox)
                std::cout << "Word type: " << textbox->getText() << std::endl;
            else if (defiViewAttachType.at(i) == DefiViewType::DEFINITION && textbox)
                std::cout << "defi: " << textbox->getText() << std::endl;
        }
        prevDefiState = !prevDefiState;
    });
    confirmButtonPtr = confirmButton.get();

    const sf::Vector2f cancelPos(0.f, -63.f);
    SpriteButtonView::Ptr cancelButton = ModDefButtonFactory::create(this, mTextureManager.get(TextureID::cancel), mFontManager.get(FontID::open_sans), cancelPos,
    [&](EventListener *listener, const sf::Event &event)
    {
        prevDefiState = !prevDefiState;
    });
    confirmButton->attachView(std::move(cancelButton));

    defiHeaderPtr->attachView(std::move(newWordTextBox));
    if (defiViewBackground->getViews().size() == 0)
        defiViewBackground->attachView(std::move(addWordTypeButton));
    else
    {
        addWordTypeButton->setPosition(10.f, 50.f);
        defiViewBackground->getViews().at(defiViewBackground->getViews().size() - 1)->attachView(std::move(addWordTypeButton));
    }
    attachView(std::move(confirmButton));
}

void DictionaryActivity::detachEditComponents()
{
    defiHeaderPtr->detachAllViews();
    defiViewBackground->detachAllViews();
    detachView(*confirmButtonPtr);
    defiTextPosition = sf::Vector2f(25.f, 28.f);
    defiViewAttachType.clear();
}

void DictionaryActivity::attachDefiComponents()
{
    const sf::Vector2f addFavButtonPos(413.f, 85.f);
    ToggleButtonView::Ptr addFavButton = AddFavButtonFactory::create(this, mTextureManager.get(TextureID::add_fav), mFontManager.get(FontID::dm_sans), addFavButtonPos,
    [&](EventListener *listener, const sf::Event &event)
    {
        ToggleButtonView *button = dynamic_cast<ToggleButtonView *>(listener);
        if (button->getState())
            addFavorites(displayTextPtr->getText());
        else
            removeFromFavorites(displayTextPtr->getText());
    });
    addFavButtonPtr = addFavButton.get();

    const sf::Vector2f editDefButtonPos(505.f, 85.f);
    SpriteButtonView::Ptr editDefButton = EditDefButtonFactory::create(this, mTextureManager.get(TextureID::edit_defi), mFontManager.get(FontID::dm_sans), editDefButtonPos,
    [&](EventListener *listener, const sf::Event &event)
    {
        // edit defi
    });

    const sf::Vector2f addDefButtonPos(1212.f, 620.f);
    SpriteButtonView::Ptr addDefButton = ModDefButtonFactory::create(this, mTextureManager.get(TextureID::add_defi), mFontManager.get(FontID::dm_sans), addDefButtonPos,
    [&](EventListener *listener, const sf::Event &event)
    {
        prevDefiState = !prevDefiState;
    });
    addDefButtonPtr = addDefButton.get();

    defiHeaderPtr->attachView(std::move(addFavButton));
    defiHeaderPtr->attachView(std::move(editDefButton));
    attachView(std::move(addDefButton));
    displayDefi("halloo");
}

void DictionaryActivity::detachDefiComponents()
{
    defiHeaderPtr->detachAllViews();
    defiViewBackground->detachAllViews();
    detachView(*addDefButtonPtr);
    displayTextPtr = nullptr;
    defiTextPosition = sf::Vector2f(25.f, 28.f);
    defiViewAttachType.clear();
}

void DictionaryActivity::setDefiState(bool defiState)
{
    this->defiState = defiState;
    if (defiState)
    {
        detachEditComponents();
        attachDefiComponents();
    }
    else
    {
        detachDefiComponents();
        attachEditComponents();
    }
}

void DictionaryActivity::attachWordTypeTextbox()
{
    const sf::Vector2f textboxPos(defiTextPosition);
    defiTextPosition += sf::Vector2f(0.f, 50.f);

    EditTextOnScrollView::Ptr wordTypeTextbox = NewWordTypeFactory::create(this, mFontManager.get(FontID::open_sans), textboxPos, defiViewBackground);
    defiViewBackground->attachView(std::move(wordTypeTextbox));
    addWordTypeButtonPtr->setPosition(addWordTypeButtonPtr->getPosition().x, addWordTypeButtonPtr->getPosition().y + 50.f);
    defiViewAttachType.push_back(DefiViewType::WORD_TYPE);
}

void DictionaryActivity::attachDefiTextbox()
{
    const sf::Vector2f textboxPos(defiTextPosition);
    defiTextPosition += sf::Vector2f(0.f, 50.f);

    EditTextOnScrollView::Ptr defiTextbox = NewDefiFactory::create(this, mFontManager.get(FontID::open_sans), textboxPos, defiViewBackground,
        [&](EventListener *listener, const sf::Event &event)
        {
            EditTextOnScrollView *textbox = dynamic_cast<EditTextOnScrollView *>(listener);
            auto foundTextbox = std::find_if(defiViewBackground->getViews().begin(), defiViewBackground->getViews().end(), [&](const ViewGroup::Ptr &p) -> bool
                                            { return p.get() == textbox; });
            if (textbox->alertDropdown())
            {
                std::cout << "push line down\n";
                for (auto it = foundTextbox + 1; it != defiViewBackground->getViews().end(); it++)
                {
                    it->get()->setPosition(it->get()->getPosition().x, it->get()->getPosition().y + 20.f);
                }
                addWordTypeButtonPtr->setPosition(addWordTypeButtonPtr->getPosition().x, addWordTypeButtonPtr->getPosition().y + 20.f);
                defiTextPosition += sf::Vector2f(0.f, 20.f);
            }
            else if (textbox->alertWrapUp())
            {
                std::cout << "wrap line up\n";
                for (auto it = foundTextbox + 1; it != defiViewBackground->getViews().end(); it++)
                {
                    it->get()->setPosition(it->get()->getPosition().x, it->get()->getPosition().y - 20.f);
                }
                addWordTypeButtonPtr->setPosition(addWordTypeButtonPtr->getPosition().x, addWordTypeButtonPtr->getPosition().y - 20.f);
                defiTextPosition -= sf::Vector2f(0.f, 20.f);
            }
            textbox->disableAlerts();
        });
    defiViewBackground->attachView(std::move(defiTextbox));
    addWordTypeButtonPtr->setPosition(addWordTypeButtonPtr->getPosition().x, addWordTypeButtonPtr->getPosition().y + 50.f);
    defiViewAttachType.push_back(DefiViewType::DEFINITION);
}

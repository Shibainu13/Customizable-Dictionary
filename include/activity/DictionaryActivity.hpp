#ifndef DICTIONARY_ACTIVITY_HPP
#define DICTIONARY_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>
#include <AppConfig.hpp>
#include <Trie.h>
#include <DatasetIdentifiers.h>

#include <DictionaryButtonFactory.hpp>
#include <DailyButtonFactory.hpp>
#include <FavButtonFactory.hpp>
#include <GameButtonFactory.hpp>
#include <SetLangButtonFactory.hpp>
#include <LogOutButtonFactory.hpp>
#include <ModeButtonFactory.hpp>
#include <EditDefButtonFactory.hpp>
#include <EditDictButtonFactory.hpp>
#include <AddFavButtonFactory.hpp>
#include <ModDefButtonFactory.hpp>
#include <SuggestButtonFactory.hpp>
#include <SetStateButtonView.hpp>
#include <WordButtonView.hpp>
#include <NewDefiButtonFactory.hpp>

#include <SearchBarFactory.hpp>
#include <NewWordFactory.hpp>
#include <NewWordTypeFactory.hpp>
#include <NewDefiFactory.hpp>

#include <SideViewFactory.hpp>
#include <DefiViewFactory.hpp>
#include <RectangleView.hpp>
#include <TextView.hpp>

#include <list>

class DictionaryActivity : public Activity
{
private:
    static constexpr int MAX_SUGGESTIONS = 4;
    static constexpr int DEFAULT_HISTORY_QUANTITY = 20;
    static constexpr int DEFAULT_RANDOM_QUANTITY = 10;
    std::string ModeBackgroundTexts[2]{"Search word to definition", "Search definition to word"};
    enum DictionaryMode
    {
        WORD_TO_DEF,
        DEF_TO_WORD,
        COUNT
    };
    enum SidebarState
    {
        HISTORY,
        DAILY,
        FAVORITE
    };
    enum SideButtonMark
    {
        DELETE,
        REMOVE,
        NONE
    };
    enum DefiViewType
    {
        BUTTON,
        WORD_TYPE,
        DEFINITION
    };

protected:
    virtual void onEvent(const sf::Event &event) override;
    virtual void onCreate() override;
    virtual void onLoadResource() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    virtual void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt) override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data) override;

private:
    void createDictionaryFromOrigin();
    void loadDictionary();
    void saveDictionary();

    void createHeader();
    RectangleView::Ptr createSearchbar();
    ColoredButtonView::Ptr createSetLangButton();
    void createSidebar();
    void createDefinitionView();

    bool getCurrentMode() const;
    void toggleMode();

    Datasets::ID getCurrentDataset() const;
    void toggleDataset();

    std::vector<std::string> getSuggestions(std::string &subWord);
    void updateSuggestButtons(std::vector<std::string> &suggestions);
    void emptySuggestButtons();
    bool isSuggestButtonsHovering(const sf::Event &event);
    void emptySideButtons();
    void updateSideButtons(std::vector<std::string> &sideButtons);
    void setSidebarState(SidebarState state);
    void adjustSideViewScroll();
    bool isSideButtonsHovering(const sf::Event &event);

    void getHistory();
    void addHistory(const std::string &word);
    void removeFromHistory(const std::string &word);

    void getRandomWords(unsigned int quantity);

    void getFavorites();
    void addFavorites(const std::string &word);
    void removeFromFavorites(const std::string &word);

    void markSideButton(SideButtonMark mark);
    void removeMarks();

    void displayDefi(const std::string &word);
    void displayHeaderText(const std::string &word);
    void displayEngEngDefi();
    void displayOtherDefi();

    void attachDefiComponents();
    void detachDefiComponents();
    void attachEditComponents();
    void detachEditComponents();

    void setDefiState(bool defiState); // true to enable defi view, disable edit view and vice versa.
    void attachWordTypeTextbox();
    void attachDefiTextbox();

private:
    FontManager mFontManager;
    TextureManager mTextureManager;

    Trie *tries[Datasets::ID::Count];
    Trie *currentTrie;

    ScrollRectView *sideViewBackground;
    SidebarState sidebarState;
    SideButtonMark sideButtonMark;

    bool currentMode;
    bool delFlag;
    bool removeFlag;
    std::string wordFlagged;

    std::list<ColoredButtonView *> suggestButtons;
    std::list<WordButtonView *> sideWordButtons;
    std::list<SpriteView *> sideButtonMarks;

    std::vector<std::string> historyWords;
    std::vector<std::string> dailyWords[Datasets::ID::Count];
    std::vector<std::string> favWords;

    ScrollRectView *defiViewBackground;
    RectangleView *defiHeaderPtr;
    TextView *displayTextPtr;
    SpriteButtonView *confirmButtonPtr;
    SpriteButtonView *addDefButtonPtr;
    ToggleButtonView *addFavButtonPtr;
    WordButtonView *addWordTypeButtonPtr;
    WordButtonView *addDefiLineButtonPtr;
    EditTextView *newWordTextboxPtr;

    std::vector<std::pair<std::string, std::string>> currentDefinition;
    std::vector<DefiViewType> defiViewAttachType;
    sf::Vector2f defiTextPosition;

    bool defiState, prevDefiState;
};

#endif
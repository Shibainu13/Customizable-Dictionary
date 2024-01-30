#include "Trie.h"
// Special Notice: Get the seed for random ONCE only! If not, same set of numbers every time
// extern unsigned int seed;
// unsigned int seed = time(0);
std::mt19937 generator(time(0));

Trie::Trie(Datasets::ID _type) : root(nullptr), typeOfDict(_type), num_line(0) {}

Trie::~Trie()
{
    delete root;
    root = nullptr;
}

void Trie::delete_Whole_Trie()
{
    delete root;
    root = nullptr;
    num_line = 0;
}

void Trie::build_Trie_EngEng()
{
    std::ifstream fin;
    fin.open(preAdress + "English_English_original.txt");
    if (!fin.is_open())
    {
        std::cout << "File cannot open!\n";
        return;
    }
    root = new TrieNode();
    while (!fin.eof())
    {
        std::string word, defi;
        getline(fin, word, (char)9); // (char)9 indicate 'TAB'
        getline(fin, defi, '\n');
        addWordAndDefiToTrie(word, defi);
        ++num_line;
    }
    fin.close();
}

void Trie::build_Trie_From_Origin(std::string &message)
{
    std::ifstream fin;
    fin.open(preAdress + originFileName[typeOfDict]);

    if (!fin.is_open())
    {
        message = "File cannot open!";
        return;
    }
    root = new TrieNode();
    while (!fin.eof())
    {
        std::string word, defi;
        getline(fin, word, (char)9); // (char)9 indicate 'TAB'
        getline(fin, defi, '\n');
        addWordAndDefiToTrie(word, defi);
        ++num_line;
    }
    message = "Init dictionary successfully";
    fin.close();
}

void Trie::addWordAndDefiToTrie(std::string word, std::string defi)
{
    TrieNode *cur = root;
    for (int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if (!cur->edges[index])
            cur->edges[index] = new TrieNode();
        cur = cur->edges[index];
    }
    cur->isEndOfWord = true;
    cur->definition.push_back(defi);
}

bool Trie::findWordInTrie(std::string word, std::vector<std::string> &defiList)
{
    TrieNode *cur = root;
    defiList.clear();
    for (int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if (!cur->edges[index])
        {
            return false;
        }
        cur = cur->edges[index];
    }
    if (cur->isEndOfWord)
    {
        defiList = cur->definition;
        return true;
    }
    return false;
}

bool Trie::findWordExistedToGetDefi(std::string word, std::vector<std::string> &defi)
{
    TrieNode *cur = root;
    for (int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if (!cur->edges[index])
            return false;
        cur = cur->edges[index];
    }
    if (cur->isEndOfWord)
    {
        defi = cur->definition;
        return true;
    }
    else
    {
        return false;
    }
}

void Trie::Serialization_DFS(std::string &message)
{
    std::ofstream fout;
    fout.open(preAdress + FileName[typeOfDict] + serializeName);
    if (!fout.is_open())
    {
        message = "File cannot open!";
        return;
    }
    root = root->Serialize_Traversal_DFS(fout, 0);
    fout.close();
    message = "Serialization complete!";
}

void Trie::Deserialization_DFS(std::string &message)
{
    std::ifstream fin;
    fin.open(preAdress + FileName[typeOfDict] + serializeName);
    if (!fin.is_open())
    {
        message = "File cannot open!";
        return;
    }
    std::string str1;
    getline(fin, str1, '_');
    root = new TrieNode();
    getline(fin, str1, '_');
    getline(fin, str1, '_');
    root->isEndOfWord = false;
    root = root->Deserialize_Traversal_DFS(fin, 0);
    fin.close();
    message = "Deserialization complete!";
}

///////////////////////////////////////////////////
// Question 3: Users can search for a definition.
void Trie::findWordFromSubDefi(std::string subDefi, std::vector<std::string> &ans)
{
    root->checkSubString("", subDefi, ans, checkerST);
}

///////////////////////////////////////////////////
// Question 5: Users can add a new word and its definition
// ham addword

///////////////////////////////////////////////////
// Question 6: Users can edit the defi of an existing word
void Trie::editExistedWordDefi(std::string word, std::string newDefi, std::string &message)
{
    // The std::cout << code below can be edit by frontend coders

    ////////////////////////////////// find the word
    TrieNode *cur = root;
    for (int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if (!cur->edges[index])
        {
            message = "There is no " + word + " in the dictionary";
            return;
        }
        cur = cur->edges[index];
    }
    if (!cur->isEndOfWord)
    {
        message = "There is no " + word + " in the dictionary";
        return;
    }
    cur->definition.clear();
    cur->definition.push_back(newDefi);
    message = "Change successfully";
}

///////////////////////////////////////////////////
// Question 7: Users can remove a word from the dictionary.
void Trie::remove_Word_FromTrie(std::string word, std::string &message)
{
    TrieNode *cur = root;
    for (int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if (!cur->edges[index])
        {
            message = "There is no " + word + " in the dictionary to remove!";
            return;
        }
        cur = cur->edges[index];
    }
    if (cur->isEndOfWord)
    {
        cur->isEndOfWord = false;
        cur->definition.clear();
        message = "Removing successfully!";
    }
    message = "There is no " + word + " in the dictionary to remove!";
}

///////////////////////////////////////////////////
// Question 8: Users can reset the dictionary to its original state.

void Trie::resetToOriginal(std::string &message)
{
    delete_Whole_Trie();
    resetFile();
    build_Trie_From_Origin(message);
    if (message == "Init dictionary successfully")
        message = "Reset dictionary successfully";
}

void Trie::resetFile()
{
    std::ofstream fo;
    fo.open(preAdress + preFavoriteName + favoriteFileName[typeOfDict]);
    fo.close();
    fo.open(preAdress + FileName[typeOfDict] + historyName);
    fo.close();
}

///////////////////////////////////////////////////
// Question 9: Users can view a word and its definition
void Trie::getRandomWordAndDefi(std::string &word, std::vector<std::string> &defiList)
{
    std::ifstream fin;
    std::string tmpWord;
    defiList.clear();
    fin.open(preAdress + originFileName[typeOfDict]);

    while (true)
    {
        int line = generator() % num_line;
        for (int i = 1; i < line; ++i)
            fin.ignore(500, '\n');
        getline(fin, tmpWord, (char)9);
        if (tmpWord == "")
            continue;
        if (findWordInTrie(tmpWord, defiList))
            break;
    }
    word = tmpWord;
    fin.close();
}

///////////////////////////////////////////////////
// Question 12: Random word - 4 defis - choose correct defi
std::string Trie::getRandomWord()
{
    std::ifstream fin;
    std::string word;
    std::vector<std::string> defi;
    fin.open(preAdress + originFileName[typeOfDict]);

    if (!fin.is_open())
        throw std::runtime_error(preAdress + originFileName[typeOfDict] + " not found.");

    while (true)
    {
        int line = generator() % num_line;
        for (int i = 1; i < line; ++i)
            fin.ignore(500, '\n');
        getline(fin, word, (char)9);
        if (findWordExistedToGetDefi(word, defi))
            break;
    }
    fin.close();
    return word;
}

std::string Trie::getRandomDefi_Of_Random_Word()
{
    std::ifstream fin;
    std::string word;
    std::vector<std::string> defi;
    fin.open(preAdress + originFileName[typeOfDict]);
    while (true)
    {
        int line = generator() % num_line;
        for (int i = 1; i < line; ++i)
            fin.ignore(500, '\n');
        getline(fin, word, (char)9);
        if (findWordExistedToGetDefi(word, defi))
            break;
    }
    fin.close();
    int bound = defi.size();
    int index_defi = generator() % bound;
    return defi[index_defi];
}

std::string Trie::getRandomDefi_Of_Its_Word(std::string word)
{
    TrieNode *cur = root;
    std::string defi;
    for (int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        cur = cur->edges[index];
    }
    if (cur->isEndOfWord)
    {
        int bound = cur->definition.size();
        int index_defi = generator() % bound;
        defi = cur->definition[index_defi];
    }
    return defi;
}

void Trie::quiz_1Word4Defis(std::string &question, std::vector<std::string> &choices, int &correctChoiceID)
{
    std::string word = getRandomWord();
    std::string correct_defi = getRandomDefi_Of_Its_Word(word);
    std::string wrong_defi1 = getRandomDefi_Of_Random_Word();
    std::string wrong_defi2 = getRandomDefi_Of_Random_Word();
    std::string wrong_defi3 = getRandomDefi_Of_Random_Word();

    std::vector<std::string> defis = {correct_defi, wrong_defi1, wrong_defi2, wrong_defi3};
    shuffle(defis.begin(), defis.end(), std::default_random_engine(generator()));

    question = word;

    choices = defis;

    for (int i = 0; i < 4; ++i)
        if (defis[i] == correct_defi)
            correctChoiceID = i;
}

void Trie::quiz_1Defi4Words(std::string &question, std::vector<std::string> &choices, int &correctChoiceID)
{
    std::string correct_word = getRandomWord();
    std::string defi = getRandomDefi_Of_Its_Word(correct_word);
    std::string wrong_word1 = getRandomWord();
    std::string wrong_word2 = getRandomWord();
    std::string wrong_word3 = getRandomWord();

    std::vector<std::string> words = {correct_word, wrong_word1, wrong_word2, wrong_word3};
    shuffle(words.begin(), words.end(), std::default_random_engine(generator()));

    question = defi;
    choices = words;
    for (int i = 0; i < 4; ++i)
        if (words[i] == correct_word)
            correctChoiceID = i;
}

void Trie::prepare_1Word4Defis()
{
    std::vector<std::string> wordSet(10);
    std::vector<std::vector<std::string>> defiSet(10);
    std::vector<int> correctOption(10);
    for (int i = 0; i < 10; ++i)
        getComponent_1Word4Defis(wordSet, defiSet, correctOption, i);
}

void Trie::getComponent_1Word4Defis(std::vector<std::string> &wordSet, std::vector<std::vector<std::string>> &defiSet,
                                    std::vector<int> &correctOption, int index)
{
    std::string word = getRandomWord();
    std::string correct_defi = getRandomDefi_Of_Its_Word(word);
    std::string wrong_defi1 = getRandomDefi_Of_Random_Word();
    std::string wrong_defi2 = getRandomDefi_Of_Random_Word();
    std::string wrong_defi3 = getRandomDefi_Of_Random_Word();

    std::vector<std::string> defis = {correct_defi, wrong_defi1, wrong_defi2, wrong_defi3};
    shuffle(defis.begin(), defis.end(), std::default_random_engine(generator()));

    wordSet[index] = word;
    defiSet[index] = defis;
    for (int i = 0; i < 4; ++i)
        if (correct_defi == defis[i])
            correctOption[index] = i;
}

void Trie::prepare_1Defi4Words()
{
    std::vector<std::string> defiSet(10);
    std::vector<std::vector<std::string>> wordSet(10);
    std::vector<int> correctOption(10);
    for (int i = 0; i < 10; ++i)
        getComponent_1Word4Defis(defiSet, wordSet, correctOption, i);
}

void Trie::getComponent_1Defi4Words(std::vector<std::string> &defiSet, std::vector<std::vector<std::string>> &wordSet,
                                    std::vector<int> &correctOption, int index)
{
    std::string correct_word = getRandomWord();
    std::string defi = getRandomDefi_Of_Its_Word(correct_word);
    std::string wrong_word1 = getRandomWord();
    std::string wrong_word2 = getRandomWord();
    std::string wrong_word3 = getRandomWord();

    std::vector<std::string> words = {correct_word, wrong_word1, wrong_word2, wrong_word3};
    shuffle(words.begin(), words.end(), std::default_random_engine(generator()));

    defiSet[index] = defi;
    wordSet[index] = words;
    for (int i = 0; i < 4; ++i)
        if (correct_word == words[i])
            correctOption[index] = i;
}

// Favourite list
// Question 2 : User can search for a keyword. Users can add the word to their favorite list.
void Trie::searchForAWord_withSuggestion(std::string &subWord, std::vector<std::string> &suggest)
{
    TrieNode *cur = root;
    for (int i = 0; i < subWord.length(); i++)
    {
        int index = convertCharToNum(subWord[i]);
        if (cur->edges[index] == nullptr)
            return;
        cur = cur->edges[index];
    }

    if (cur->isEndOfWord)
        suggest.push_back(subWord);

    cur->allSuggestWord(subWord, suggest);
}

void Trie::search_and_addToFavoriteList(std::string &subWord)
{
    std::vector<std::string> test;
    searchForAWord_withSuggestion(subWord, test);
    for (int i = 0; i < test.size(); i++)
        std::cout << "[" << i + 1 << "] " << test[i] << "\n";

    int choice;
    std::cout << "Your choice is : ";
    std::cin >> choice;

    std::ofstream fout(preAdress + preFavoriteName + favoriteFileName[typeOfDict], std::ios_base::app);
    if (!fout.is_open())
        std::cout << "File not found";
    else
        fout << test[choice - 1] << "\n";
    fout.close();
}

void Trie::addToFavoriteList(std::string word, std::string &message)
{
    std::ofstream fout(preAdress + preFavoriteName + favoriteFileName[typeOfDict], std::ios_base::app);
    if (!fout.is_open())
    {
        message = "File not found";
        return;
    }
    fout << word << "\n";
    message = "Adding to Favorite list successfully!";
    fout.close();
}

// Question 10 : User can view their favorite list
void Trie::readData_FavoriteList(std::vector<std::string> &fav, std::string &message)
{
    fav.clear();
    std::ifstream fin;
    fin.open(preAdress + preFavoriteName + favoriteFileName[typeOfDict]);
    if (!fin.is_open())
    {
        message = "File not found\n";
        return;
    }
    std::string word;
    while (fin >> word)
        fav.push_back(word);
    fin.close();
    message = "View Favorite List successfully!";
}

void Trie::viewFavoriteList(std::vector<std::string> &fav, std::string &message)
{
    readData_FavoriteList(fav, message);
}

// Question 11 : User can remove a word from their favorite list.
void Trie::removeAWordFromFavoriteList(int order, std::string &message)
{
    std::vector<std::string> fav;
    readData_FavoriteList(fav, message);

    std::ofstream fout(preAdress + preFavoriteName + favoriteFileName[typeOfDict], std::ios_base::trunc);
    if (!fout.is_open())
    {
        message = "File not found!";
        return;
    }

    for (int i = 0; i < fav.size(); i++)
    {
        if (i != order - 1)
        {
            fout << fav[i] << "\n";
        }
    }
    fout.close();
    message = "Remove successfully!";
}

void Trie::addToHistory(std::string word, std::string &message)
{
    std::ofstream fout(preAdress + FileName[typeOfDict] + historyName, std::ios_base::app);
    if (fout.is_open())
    {
        fout << word << "\n";
    }
    else
    {
        message = "Error opening file !";
        return;
    }
    fout.close();
}

void Trie::takeHistory(std::vector<std::string> &historyList, std::string &message)
{
    historyList.clear();
    std::ifstream fin(preAdress + FileName[typeOfDict] + historyName);
    if (fin.is_open())
    {
        std::string s;
        while (getline(fin, s))
        {
            auto found = std::find(historyList.begin(), historyList.end(), s);
            if (found == historyList.end())
                historyList.push_back(s);
        }
    }
    else
    {
        message = "Error opening file !";
        return;
    }
    fin.close();
    std::reverse(historyList.begin(), historyList.end());
}

void Trie::removeFromHistory(const std::string &word, std::string &message)
{
    std::vector<std::string> currentHistory;
    takeHistory(currentHistory, message);

    auto found = std::find(currentHistory.begin(), currentHistory.end(), word);
    if (found == currentHistory.end())
        return;
    currentHistory.erase(found);

    std::ofstream fout(preAdress + FileName[typeOfDict] + historyName);
    for (auto &word : currentHistory)
        addToHistory(word, message);
}

void splitEachDefi(std::string tmp, std::pair<std::string, std::string> &ans)
{
    std::string s;
    std::string st;
    s = "";
    st = "";
    int cnt = 0;
    char pre = 's';
    for (char c : tmp)
    {
        if (c == ' ' && pre == ')' && !cnt)
        {
            ++cnt;
            continue;
        }
        if (!cnt)
            s += c;
        else
            st += c;
        pre = c;
    }
    ans = std::make_pair(s, st);
}

void split_Definition(std::vector<std::string> &defiList, std::vector<std::pair<std::string, std::string>> &ans)
{
    ans.clear();
    for (std::string tmp : defiList)
    {
        std::pair<std::string, std::string> defiAfterSplit;
        splitEachDefi(tmp, defiAfterSplit);
        ans.push_back(defiAfterSplit);
    }
    sort(ans.begin(), ans.end());
}

auto Trie::take_First_K_Word(int k) -> std::vector<std::string>
{
    std::string tmp = "";
    std::vector<std::string> ans;
    root->takeKWord(tmp, k, ans);
    return ans;
}

Datasets::ID Trie::getCurrentDataset() const
{
    return typeOfDict;
}
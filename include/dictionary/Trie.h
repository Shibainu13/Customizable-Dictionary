#ifndef TRIE_H
#define TRIE_H

#include "DatasetIdentifiers.h"
#include "TrieNode.h"
#include "checkerSubString.h"

#include <queue>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <fstream>

const std::string preAdress = "data_set/";
const std::string FileName[4] = {"English_English", "English_Vietnamese", "Vietnamese_English", "slang_emoji"};
const std::string originFileName[4] = {"English_English_original.txt", "English_Vietnamese_original.txt",
                                       "Vietnamese_English_original.txt", "slang_emoji_original.txt"};
const std::string favoriteFileName[4] = {"_Eng_Eng.txt", "_Eng_Viet.txt", "_Viet_Eng.txt", "_emoji.txt"};
const std::string preFavoriteName = "favorite";
const std::string serializeName = "_serializationDFS.txt";
const std::string historyName = "_history.txt";

class Trie
{
public:
    int num_line;

    Trie(Datasets::ID _type);
    ~Trie();

    void build_Trie_EngEng();
    void build_Trie_From_Origin(std::string &message);
    void delete_Whole_Trie();
    void resetToOriginal(std::string &message);
    void resetFile();

    void Serialization_DFS(std::string &message);
    void Deserialization_DFS(std::string &message);

    void remove_Word_FromTrie(std::string word, std::string &message);
    void addWordAndDefiToTrie(std::string word, std::string defi);
    bool findWordInTrie(std::string word, std::vector<std::string> &defiList);
    bool findWordExistedToGetDefi(std::string word, std::vector<std::string> &defi);
    void findWordFromSubDefi(std::string subDefi, std::vector<std::string> &ans);
    void editExistedWordDefi(std::string word, std::string newDefi, std::string &message);

    void getRandomWordAndDefi(std::string &word, std::vector<std::string> &defiList);
    std::string getRandomWord();
    std::string getRandomDefi_Of_Its_Word(std::string word);
    std::string getRandomDefi_Of_Random_Word();

    void quiz_1Word4Defis(std::string &question, std::vector<std::string> &choices, int &correctChoiceID);
    void quiz_1Defi4Words(std::string &question, std::vector<std::string> &choices, int &correctChoiceID);
    void choose_1Word4Defis();
    void choose_1Defi4Words();

    void prepare_1Word4Defis();
    void getComponent_1Word4Defis(std::vector<std::string> &wordSet, std::vector<std::vector<std::string>> &defiSet,
                                  std::vector<int> &correctOption, int index);
    void prepare_1Defi4Words();
    void getComponent_1Defi4Words(std::vector<std::string> &defiSet, std::vector<std::vector<std::string>> &wordSet,
                                  std::vector<int> &correctOption, int index);

    // Favourite list task
    void searchForAWord_withSuggestion(std::string &subWord, std::vector<std::string> &suggest);
    void search_and_addToFavoriteList(std::string &subWord);
    void addToFavoriteList(std::string word, std::string &message);
    void viewFavoriteList(std::vector<std::string> &fav, std::string &message);
    void removeAWordFromFavoriteList(const std::string& word, std::string &message);

    // History task
    void addToHistory(std::string word, std::string &message);
    void takeHistory(std::vector<std::string> &historyList, std::string &message);
    void removeFromHistory(const std::string &word, std::string &message);

    // Phong task
    auto take_First_K_Word(int k) -> std::vector<std::string>;

    Datasets::ID getCurrentDataset() const;

private:
    void readData_FavoriteList(std::vector<std::string> &fav, std::string &message);

    TrieNode *root;
    Datasets::ID typeOfDict;
    checker checkerST;
};

// Additional function
void splitEachDefi(std::string tmp, std::pair<std::string, std::string> &ans);
void split_Definition(std::vector<std::string> &defiList, std::vector<std::pair<std::string, std::string>> &ans);
#endif

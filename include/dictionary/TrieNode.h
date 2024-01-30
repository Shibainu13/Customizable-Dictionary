#ifndef TRIENODE_H
#define TRIENODE_H

#include "checkerSubString.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

constexpr int TrieSize = 69;

int convertCharToNum(char c);
char convertNumToChar(int n);

struct TrieNode
{
public:
    TrieNode()
    {
        for (int i = 0; i < TrieSize; ++i)
            edges[i] = nullptr;
        isEndOfWord = false;
    }

    ~TrieNode()
    {
        for (int i = 0; i < TrieSize; ++i)
            delete edges[i];
    }

    auto Serialize_Traversal_DFS(std::ofstream &fout, int index) -> TrieNode *;
    auto Deserialize_Traversal_DFS(std::ifstream &fin, int index) -> TrieNode *;

    // Favourite list

    void allSuggestWord(std::string &subWord, std::vector<std::string> &suggest);

    // Question 3

    void checkSubString(std::string curWord, std::string &subDefi, std::vector<std::string> &ans, checker &checkST);

    // Phong request

    void takeKWord(std::string &word, int need, std::vector<std::string> &ans);

public:
    TrieNode *edges[TrieSize];
    bool isEndOfWord;
    std::vector<std::string> definition;
};

#endif
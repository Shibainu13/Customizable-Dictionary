#include "TrieNode.h"

////////////////////////////////////////////////// General function
int convertCharToNum(char c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    else if ('!' <= c && c <= '/')
        return c - '!' + 10;
    else if (':' <= c && c <= '@')
        return c - ':' + 25;
    else if ('[' <= c && c <= '`')
        return c - '[' + 32;
    else if ('{' <= c && c <= '~')
        return c - '{' + 38;
    else if (c == 32) // Space character
        return 42;
    else if ('a' <= c && c <= 'z')
        return c - 'a' + 43;
    else if ('A' <= c && c <= 'Z')
        return c - 'A' + 43;
    return -1;
}

char convertNumToChar(int n)
{
    if (0 <= n && n <= 9)
        return n + '0';
    else if (10 <= n && n <= 24)
        return n + '!' - 10;
    else if (25 <= n && n <= 31)
        return n + ':' - 25;
    else if (32 <= n && n <= 37)
        return n + '[' - 32;
    else if (38 <= n && n <= 41)
        return n + '{' - 38;
    else if (n == 42) // Space character
        return 32;
    else if (43 <= n && n <= 68)
        return n + 'a' - 43;
    return 0;
}

//////////////////////////////////////////////////////////////////

auto TrieNode::Serialize_Traversal_DFS(std::ofstream &fout, int index) -> TrieNode *
{
    // if(!this)
    //     return this;
    fout << "node_";
    fout << index << "_";
    if (this->isEndOfWord == false)
        fout << "0_";
    else
    {
        fout << "1_";
        for (int i = 0; i < this->definition.size(); ++i)
        {
            if (i == this->definition.size() - 1)
                fout << this->definition[i] << '\n';
            else
                fout << this->definition[i] << "_";
        }
    }
    for (int i = 0; i < TrieSize; ++i)
        if (this->edges[i])
            this->edges[i] = this->edges[i]->Serialize_Traversal_DFS(fout, i);
    fout << "#_";
    return this;
}

auto TrieNode::Deserialize_Traversal_DFS(std::ifstream &fin, int index) -> TrieNode *
{
    std::string str;
    getline(fin, str, '_');
    if (str == "#")
        return this;
    else if (str == "node")
    {
        fin >> index;
        fin.ignore(10, '_');
        this->edges[index] = new TrieNode();
        getline(fin, str, '_');
        if (str == "0")
            this->edges[index]->isEndOfWord = false;
        else if (str == "1")
        {
            this->edges[index]->isEndOfWord = true;
            getline(fin, str, '\n');
            std::stringstream s;
            s << str;
            while (!s.eof())
            {
                getline(s, str, '_');
                this->edges[index]->definition.push_back(str);
            }
        }
        this->edges[index] = this->edges[index]->Deserialize_Traversal_DFS(fin, 0);
    }
    return this->Deserialize_Traversal_DFS(fin, index);
}

void TrieNode::allSuggestWord(std::string &subWord, std::vector<std::string> &suggest)
{
    for (int i = 0; i < TrieSize; i++)
    {
        if (this->edges[i] != nullptr)
        {
            subWord += convertNumToChar(i);
            if (this->edges[i]->isEndOfWord)
                suggest.push_back(subWord);
            this->edges[i]->allSuggestWord(subWord, suggest);
            subWord.pop_back();
        }
    }
}

void TrieNode::takeKWord(std::string &word, int need, std::vector<std::string> &ans)
{
    for (int i = 0; i < TrieSize; ++i)
    {
        if (!this->edges[i])
            continue;

        word += convertNumToChar(i);
        if (this->edges[i]->isEndOfWord)
            ans.push_back(word);
        if (ans.size() == need)
            return;
        this->edges[i]->takeKWord(word, need, ans);
        if (ans.size() == need)
            return;
        word.pop_back();
    }
}

void TrieNode::checkSubString(std::string curWord, std::string &subDefi, std::vector<std::string> &ans, checker &checkST)
{
    for (int i = 0; i < TrieSize; ++i)
    {
        if (this->edges[i] == nullptr)
            continue;

        curWord += convertNumToChar(i);
        if (this->edges[i]->isEndOfWord)
        {
            for (std::string defi : this->edges[i]->definition)
                if (checkST.checkSubString(subDefi, defi))
                {
                    ans.push_back(curWord);
                    break;
                }
        }
        this->edges[i]->checkSubString(curWord, subDefi, ans, checkST);
        curWord.pop_back();
    }
}

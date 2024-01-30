// #include "Trie.h"

// int main()
// {
//     // Question 1
//     // Trie *obj = new Trie(Datasets::Eng_Eng);
//     // std::string message = "";
//     // obj->build_Trie_From_Origin(message);
//     // std::vector<std::string> defiList;
//     // std::cout << message << "\n";
//     // Trie* obj[4];
//     // obj[0] = new Trie(Datasets::Eng_Eng);
//     // // Trie* obj = new Trie(Datasets::Eng_Viet);
//     // obj[2] = new Trie(Datasets::Eng_Viet);
//     // obj[3] = new Trie(Datasets::Emoji);
//     // std::string message = "";
//     // obj[2]->build_Trie_From_Origin(message);
//     // obj[2]->Serialization_DFS(message);
//     // std::cout << message << "\n";
//     // obj->Serialization_DFS(message);
//     // std::cout << message << "\n";
//     // obj->Deserialization_DFS(message);
//     // std::cout << message << "\n";
//     // std::cout << obj->findWordInTrie("'em", defiList);

//     // for(int i = 0; i < 4; ++i){
//     //     if(i == 2)
//     //         continue;
//     //     obj[i]->build_Trie_From_Origin(message);
//     //     std::cout << message << "\n";
//     // }
//     // std::cout << "------------------------------------------\n";
//     // obj[2]->Deserialization_DFS(message);
//     // std::cout << message << "\n";
//     // std::cout << obj[2]->findWordInTrie("'em", defiList) << "\n";
//     // for(std::string tmp : defiList)
//     //     std::cout << tmp << "\n";
//     // std::cout << "------------------------------------------\n";

//     // obj[0]->Serialization_DFS(message);
//     // obj[1]->Serialization_DFS(message);
//     // obj[2]->Serialization_DFS(message);
//     // obj[3]->Serialization_DFS(message);

//     // std::cout << "SET 1:\n";
//     // obj->findWordInTrie("'em");
//     // obj->findWordInTrie("'gainst");
//     // obj->findWordInTrie("apples");
//     // obj->findWordInTrie("mastax");
//     // obj->findWordInTrie("abc");
//     // obj->findWordInTrie("appeal");
//     // obj->findWordInTrie("spondaic");
//     // obj->Serialization_DFS(message);
//     // obj->delete_Whole_Trie();
//     // std::cout << message << "\n";
//     // std::cout << "------------------------------------------\n";

//     // std::cout << "SET 2:\n";
//     // obj->Deserialization_DFS(message);
//     // std::cout << message << "\n";
//     // obj->findWordInTrie("'em");
//     // obj->findWordInTrie("'gainst");
//     // obj->findWordInTrie("apples");
//     // obj->findWordInTrie("mastax");
//     // obj->findWordInTrie("abc");
//     // obj->findWordInTrie("appeal");
//     // obj->findWordInTrie("spondaic");
//     // std::cout << "------------------------------------------\n";

//     // // task 3
//     // std::vector<std::string> ans;
//     // obj->findWordFromSubDefi("An", ans);
//     // std::cout << ans.size() << "\n";
//     // int cnt = 0;
//     // for(std::string tmp : ans){
//     //     ++cnt;
//     //     std::cout << tmp << "\n";
//     //     if(cnt == 5)
//     //         break;
//     // }
//     // std::cout << "------------------------------------------\n";

//     // // task 2.1
//     // std::string subword = "asteroid";
//     // std::vector<std::string> suggest;
//     // suggest.clear();
//     // obj->searchForAWord_withSuggestion(subword, suggest);
//     // for(std::string tmp : suggest)
//     //     std::cout << tmp << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 2.2
//     // std::string word = "asteroidal";
//     // obj->addToFavoriteList(word, message);
//     // std::cout << message << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 4.1
//     // std::string word = "hello";
//     // message = "";
//     // obj->addToHistory(word, message);
//     // std::cout << message << " task 4.1\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 4.2
//     // std::vector<std::string> historyList;
//     // historyList.clear();
//     // message = "";
//     // obj->takeHistory(historyList, message);
//     // for(std::string tmp : historyList)
//     //     std::cout << tmp << "\n";
//     // std::cout << message << " task 4.2\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 5
//     // std::string word, defi;
//     // obj->addWordAndDefiToTrie(word, defi);

//     // // task 6
//     // message = "";
//     // defiList.clear();
//     // obj->findWordInTrie("appeal", defiList);
//     // std::vector<std::pair<std::string, std::string>> aans;
//     // split_Definition(defiList, aans);
//     // std::cout << aans.size() << "\n";

//     // for(std::pair<std::string, std::string> tmp : aans)
//     //     std::cout << tmp.first << "-" << tmp.second << "\n";
//     // std::cout << "------------------------------------------\n";

//     // obj->editExistedWordDefi("appeal", "(n) doraemon", message);

//     // message = "";
//     // defiList.clear();
//     // obj->findWordInTrie("appeal", defiList);
//     // split_Definition(defiList, aans);
//     // std::cout << aans.size() << "\n";

//     // for(std::pair<std::string, std::string> tmp : aans)
//     //     std::cout << tmp.first << "-" << tmp.second << "\n";

//     // // task 7
//     // bool ok = obj->findWordInTrie("appeal", defiList);
//     // std::cout << ok << "\n";
//     // message = "";
//     // obj->remove_Word_FromTrie("appeal", message);
//     // std::cout << "remove\n";
//     // ok = obj->findWordInTrie("appeal", defiList);
//     // std::cout << ok << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 8
//     // std::cout << obj->findWordInTrie("appeal", defiList) << "\n";
//     // obj->resetToOriginal(message);
//     // std::cout << message << "\n";
//     // std::cout << obj->findWordInTrie("appeal", defiList) << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 9
//     // std::string word;
//     // obj->getRandomWordAndDefi(word, defiList);
//     // std::cout << word << "\n";
//     // for(std::string tmp : defiList)
//     //     std::cout << tmp << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 10
//     // std::vector<std::string> fav;
//     // obj->viewFavoriteList(fav, message);
//     // for(std::string tmp : fav)
//     //     std::cout << tmp << "\n";
//     // std::cout << message << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 11
//     // obj->removeAWordFromFavoriteList(3, message);
//     // std::cout << message << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 12
//     // std::string question;
//     // std::vector<std::string> choices;
//     // int correctID;
//     // obj->quiz_1Word4Defis(question, choices, correctID);
//     // std::cout << question << "\n";
//     // for(int i = 0; i < choices.size(); ++i)
//     //     std::cout << "A. " << choices[i] << "\n";
//     // std::cout << correctID << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // task 13
//     // obj->quiz_1Defi4Words(question, choices, correctID);
//     // std::cout << question << "\n";
//     // for(int i = 0; i < choices.size(); ++i)
//     //     std::cout << "A. " << choices[i] << "\n";
//     // std::cout << correctID << "\n";
//     // std::cout << "------------------------------------------\n";

//     // // Question 7
//     // obj->findWordInTrie("appealable");
//     // obj->remove_Word_FromTrie("appealable");
//     // obj->findWordInTrie("appealable");
//     // std::cout << "------------------------------------------\n";

//     // // Question 9
//     // obj->getRandomWordAndDefi();
//     // std::cout << "------------------------------------------\n";

//     // // Question 12
//     // obj->quiz_1Word4Defis();
//     // std::cout << "------------------------------------------\n";

//     // // Question 13
//     // obj->quiz_1Defi4Words();
//     // std::cout << "------------------------------------------\n";

//     // Do not delete because we already have destructor
//     // delete obj[0];
//     // delete obj;
//     // delete obj[2];
//     // delete obj[3];
//     // delete obj;
//     return 0;
// }
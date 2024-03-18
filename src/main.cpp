#include <Application.hpp>
#include <ActivityFactory.hpp>
#include <DictionaryActivity.hpp>
#include <SignInActivity.hpp>
#include <AppConfig.hpp>
#include <UserRepo.hpp>

int main()
{
    AppConfig &config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WINDOW_SIZE);
    std::string windowTitle = config.get<std::string>(ConfigKey::APP_NAME);

    Application app(windowSize.x, windowSize.y, windowTitle);
    Activity::Ptr launcher = std::make_unique<SignInActivity>();
    app.addLauncher(std::move(launcher));
    app.run();
}

// // #include <SFML/Graphics.hpp>

// // int main()
// // {
// //     // Create the window
// //     sf::RenderWindow window(sf::VideoMode(800, 800), "Independent Scrolling Views");

// //     // Create two separate views
// //     sf::View leftView(sf::FloatRect(0, 0, 800, 800));
// //     sf::View middleView(sf::FloatRect(0, 0, 800, 800));
// //     sf::View rightView(sf::FloatRect(0, 0, 800, 800));

// //     leftView.setViewport(sf::FloatRect(0, 0, 0.5, 1));
// //     middleView.setViewport(sf::FloatRect(0.5, 0, 0.25, 1));
// //     rightView.setViewport(sf::FloatRect(0.75, 0, 0.25, 1));

// //     // Set initial view positions
// //     // leftView.setCenter(200, 300);
// //     // middleView.setCenter(300, 300);

// //     // Create some drawable entities
// //     sf::RectangleShape rectangle(sf::Vector2f(800, 50));
// //     rectangle.setFillColor(sf::Color::Yellow);
// //     rectangle.setPosition(0, 0);

// //     sf::RectangleShape rectangle1(sf::Vector2f(50, 50));
// //     rectangle1.setFillColor(sf::Color::Red);
// //     rectangle1.setPosition(0, 0);

// //     sf::RectangleShape rectangle2(sf::Vector2f(50, 50));
// //     rectangle2.setFillColor(sf::Color::Blue);
// //     rectangle2.setPosition(400, 0);

// //     sf::RectangleShape rectangle3(sf::Vector2f(50, 50));
// //     rectangle3.setFillColor(sf::Color::Green);
// //     rectangle3.setPosition(600, 0);

// //     // Main loop
// //     while (window.isOpen())
// //     {
// //         sf::Event event;
// //         while (window.pollEvent(event))
// //         {
// //             if (event.type == sf::Event::Closed)
// //                 window.close();
// //         }

// //         // Handle input for scrolling
// //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
// //             leftView.move(0, -5);
// //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
// //             leftView.move(0, 5);
// //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
// //             middleView.move(0, -5);
// //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
// //             middleView.move(0, 5);
// //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
// //             rightView.move(0, -5);
// //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
// //             rightView.move(0, 5);

// //         // Clear the window
// //         window.clear(sf::Color::White);
// //         window.draw(rectangle);

// //         // Set the views and draw entities
// //         window.setView(leftView);
// //         window.draw(rectangle1);

// //         window.setView(middleView);
// //         window.draw(rectangle2);

// //         window.setView(rightView);
// //         window.draw(rectangle3);

// //         // Display the contents
// //         window.setView(window.getDefaultView());
// //         window.display();
// //     }

// //     return 0;
// // }

// #include <SFML/Graphics.hpp>
// #include <iostream>

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Sidebar Scrolling");

//     sf::RectangleShape sidebar(sf::Vector2f(200.f, 600.f));
//     sidebar.setFillColor(sf::Color(150, 150, 150));

//     sf::Font font;
//     font.loadFromFile("res/font/DM_Sans/DMSans-Italic-VariableFont_opsz,wght.ttf"); // Replace with the path to your font file

//     sf::Text content("Lorem ipsum dolor sit amet, consectetur adipiscing elit.", font, 16);
//     content.setFillColor(sf::Color::Black);
//     content.setPosition(30, 30);

//     sf::View sidebarView(sf::FloatRect(0.f, 0.f, 200.f, 600.f));
//     sidebarView.setViewport(sf::FloatRect(0, 0.5, 0.2, 1));

//     // Set the initial view
//     window.setView(sidebarView);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();

//             // Handle mouse wheel scrolling
//             if (event.type == sf::Event::MouseWheelScrolled)
//             {
//                 if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
//                 {
//                     // Adjust the view position based on the mouse wheel movement
//                     sidebarView.move(0.f, -event.mouseWheelScroll.delta * 10.f);
//                     std::cout << window.mapPixelToCoords(sf::Mouse::getPosition(window), sidebarView).x << ' ' << window.mapPixelToCoords(sf::Mouse::getPosition(window), sidebarView).y << std::endl;
//                     std::cout << sf::Mouse::getPosition(window).x << ' ' << sf::Mouse::getPosition(window).x << std::endl;
//                 }
//             }
//         }
//         window.clear(sf::Color::White);
//         window.setView(sidebarView);
//         // Draw sidebar background
//         window.draw(sidebar);
//         window.draw(content);
//         // Set the view for drawing the content
//         window.setView(window.getDefaultView()); // Reset to the default view

//         window.display();
//         sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), sidebarView);
//         std::cout << pos.x << ' ' << pos.y << std::endl;
//         std::cout << sf::Mouse::getPosition(window).x << ' ' << sf::Mouse::getPosition(window).y << std::endl;
//     }

//     return 0;
// }

// #include "Trie.h"

// int main()
// {
//     // Question 1
//     Trie *obj = new Trie(Datasets::Eng_Eng);
//     std::string message = "";
//     obj->build_Trie_From_Origin(message);
//     std::vector<std::string> defiList;
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

//     // task 9
//     std::string word1 = obj->getRandomWord();
//     std::cout << word1 << "\n";
//     std::string word2 = obj->getRandomWord();
//     std::cout << word2 << "\n";
//     std::string word3 = obj->getRandomWord();
//     std::cout << word3 << "\n";
//     // for(std::string tmp : defiList)
//     //     std::cout << tmp << "\n";
//     std::cout << "------------------------------------------\n";

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
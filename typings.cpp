// Author : amanraox

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <curses.h>
#include <algorithm>

int main() {
    // open the Linux built-in wordlist
    std::ifstream wordlist("/usr/share/dict/words");

    // read all the words into a vector
    std::vector<std::string> words;
    std::string word;
    
    bool play = true;
    while (play) {

        while (wordlist >> word) {
            if (word.size() <= 5) {
                words.push_back(word);
            }
        }
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::shuffle(words.begin(), words.end(), rng);
        words.resize(10);

        auto it = words.begin();
        std::advance(it, 10);
        words.erase(it, words.end());

        // prompt the user to type out the words
        std::cout << "Type the following words:" << std::endl;
        for (const std::string &word : words) {
            std::cout << word + " ";
        }
        std::cout << "\n";

        auto start = std::chrono::steady_clock::now();
        std::string input;
        std::getline(std::cin, input);
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        std::vector<std::string> input_words;
        std::stringstream input_ss(input);
        while (input_ss >> word) {
            input_words.push_back(word);
        }

        int correct = 0;
        int incorrect = 0;
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == input_words[i]) {
                // mark correct words in green
                std::cout << "\033[1;32m" << words[i] << "\033[0m" << std::endl;
                correct++;
            }
            else {
                // mark incorrect words in red
                std::cout << "\033[1;31m" << words[i] << "\033[0m" << std::endl;
                incorrect++;
            }
        }

        int time = input.size();  
        float wpm = words.size()/(60.0/elapsed)*10;
        float accuracy = (1.0*correct) / words.size();
        std::cout << "your result Aman" << std::endl;
        std::cout << "Words per minute: " << wpm << std::endl;
        std::cout << "Time elapsed: " << elapsed << std::endl;
        std::cout << "Accuracy: " << 1.0*accuracy << std::endl;
        std::cout << "Continue y/n?" << std::endl;
        std::string answer;
        std::getline(std::cin, answer);
        if (answer == "y") {
            play = true;
        } else {
            play = false;
        } 
    }
        
    return 0;
}


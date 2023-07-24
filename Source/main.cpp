#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// IMPORTANT NOTE SMART QUOTES ARE THE WORST

// Global Variables Not a good idea but you know how it is
int depth;
std::vector<char> acceptableEndingPunctuation = {'.', '?', '!'};

std::vector<char> punctuation = {',', ';', '-', '\''};

std::vector<int> cachedIndexes;

// Prototypes
int generateRandomIndex(int min, int max);
std::vector<std::string> returnTextFileData(std::ifstream &textFile);
std::string getNextWord(const std::string &targetString, const std::string &prompt);
std::string generateSentence(std::string userPrompt, std::vector<std::string> &fileData, std::vector<int> &cachedIndexes);
void removeChars(std::string &str);

//----- Rules of the Generative AI program -----
// Ask the user for a one word prompt.
// Start a sentence with the prompt word.
// Repeat until the word ends with a period, question mark, or exclamation point:
// Open the book to a random location.
// Read words until you find the prompt word.
// Choose the next word.
// add the word to the end of the sentence.
// This word becomes the next prompt.
// When the loop exits, print the sentence.

int main() {
  srand(time(NULL));
  std::ifstream file("../Alice_and_the_Wonderland.txt");
  if (!file.is_open()) {
    std::cerr << "The file failed to open" << std::endl;
    return -1;
  }
  std::vector<std::string> fileData = returnTextFileData(file);
  file.close();

  std::string userPrompt;
  printf("Enter your prompt: ");
  std::getline(std::cin, userPrompt);
  printf("\n");

  std::string finalWord = generateSentence(userPrompt, fileData, cachedIndexes);
  std::cout << "The Final word: " << finalWord << "\n";
  return 0;
}

std::string generateSentence(std::string userPrompt, std::vector<std::string> &fileData, std::vector<int> &cachedIndexes) {
  int depth = 0;
  std::string currentPrompt = userPrompt;
  std::string finalWord = currentPrompt;

  while (depth < 25000) {
    std::cout << "THE WORD: " << finalWord << "\n";

    for (char punctuation : acceptableEndingPunctuation) {
      for (char c : finalWord) {
        if (c == punctuation) {
          return finalWord;
        }
      }
    }

    int index = generateRandomIndex(0, fileData.size() - 1);

    std::string currentWord = fileData.at(index);
    if (currentWord.empty()) continue;

    std::cout << "Current prompt: " << currentPrompt << "\n"
              << "Current word: " << currentWord << "\n";
    std::string nextWord = getNextWord(currentWord, currentPrompt);
    if (nextWord != "FAILED") {
      // Check if the next word starts with acceptable punctuation
      for (char punctuation : punctuation) {
        if (nextWord.at(0) == punctuation) {
          finalWord += nextWord;
          break;
        }
      }

      // If the next word doesn't start with punctuation, add a space before appending it
      if (finalWord.back() != ' ') {
        finalWord += ' ';
      }

      finalWord += nextWord;
      currentPrompt = nextWord;
      removeChars(currentPrompt);
    }
    depth++;
  }

  return "Depth Exceeded";
}

#include <sstream>

std::string getNextWord(const std::string &targetString, const std::string &prompt) {
  std::string ret;

  if (targetString.empty() || prompt.empty()) {
    return "FAILED";
  }

  int startPos = targetString.find(prompt);

  if (startPos != std::string::npos) {
    // Move the startPos to the end of the prompt
    startPos += prompt.length();

    // Find the position of the next space character after the prompt
    while (startPos < targetString.length() && targetString.at(startPos) != ' ') {
      startPos++;
    }

    // Check if startPos is still within bounds
    if (startPos < targetString.length()) {
      // Create a stringstream from the targetString, starting from the end of the prompt
      std::stringstream ss(targetString.substr(startPos));

      // Extract the first word from the stringstream
      if (ss >> ret) {
        return ret;
      }
    }
  }

  // If the prompt is not found or there are no words after the prompt, return "FAILED"
  return "FAILED";
}

int generateRandomIndex(int min, int max) {
  int range = max - min + 1;

  int randomNumber = rand() % range + min;

  return randomNumber;
}

std::vector<std::string> returnTextFileData(std::ifstream &textFile) {
  std::vector<std::string> ret;
  std::string currentLine;
  while (std::getline(textFile, currentLine)) {
    ret.push_back(currentLine);
  }
  return ret;
}

void removeChars(std::string &str) {
  str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return c == '\"' || c == '(' || c == ')'; }), str.end());
}
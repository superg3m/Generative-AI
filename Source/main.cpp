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

// TODO: Extra this code into its own classes
// TODO: Add extra parameters for the generative process
// TODO: fix double quotes bug
// TODO: Add more Texts and make it one amalgamation in a vector to pull from

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
  std::ifstream file("../Archive/Alice_and_the_Wonderland.txt");
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
// clang-format off

// GLOBAL VARIABLES
// std::vector<std::string> archiveTextData

// ---- Class structure ----
// File_Class(std::string fileName)
  // void format_text_file_data(std::string fileName)
  // read_and_store_file_data(std::string fileName)
    // Open and close file in this method
    // Push all data into the archiveTextData

// Generative_Ai_Class()
  // member variable int depth
  // member variable std::string currentPrompt
  // member variable std::string currentLine
  // 
  // memeber variable std::string finalWord
  // std::string getUserPrompt()
  // std::string getRandomLine(int index)
    // int generateRandomIndex(int min, int max)
    // check if prompt is found inside the randomLine
      // getNextWord(std::string randomLine, int foundIndex)
        // update currentPrompt

// clang-format on

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
      for (char punctuation : punctuation) {
        if (nextWord.at(0) == punctuation) {
          finalWord += nextWord;
          break;
        }
      }

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
    startPos += prompt.length();

    while (startPos < targetString.length() && targetString.at(startPos) != ' ') {
      startPos++;
    }

    if (startPos < targetString.length()) {
      std::stringstream ss(targetString.substr(startPos));

      if (ss >> ret) {
        return ret;
      }
    }
  }

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
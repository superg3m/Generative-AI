
#pragma once

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "./File.h"

class Generative_Ai {
 public:
  Generative_Ai();

  std::string generateSentence(int sentenceCount, const int promptWordLength, const bool useUniqueLines, const bool useSpecialChars, int passthroughs, std::vector<std::string> &fileData);

  void resetValues();

  std::vector<std::string> partitionPrompt(const std::string &prompt) const;

  std::string constructCurrentPrompt(const std::vector<std::string> &promptVector, const int promptMaxWordLength) const;

  std::string getRandomLine(const std::vector<std::string> &fileData) const;

  std::string removeSpecialCharacters(const std::string &input) const;

  std::string getUserPrompt() const;

  std::string getFirstWord(const std::string &str) const;

  std::string getNextWord(int &foundIndex) const;

  std::string getCurrentPrompt() const;

  std::string getCurrentLine() const;

  int getDepth() const;

  void setUserPrompt();

  void setDepth(const int depth);

  void setCurrentPrompt(const std::string &prompt);

  void setCurrentLine(const std::string &line);

  std::string getFinalWord();

 private:
  int generateRandomIndex(int min, int max) const;
  void eraseFirstWord(std::string &str) const;

  int depth;
  std::string currentPrompt;
  std::string randomLine;
  std::string finalWord;
  int number_of_completed_Sentences;
  int currentIndex;  // New member variable to keep track of used line indices
};
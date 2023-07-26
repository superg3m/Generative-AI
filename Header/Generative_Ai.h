
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

  std::string generateSentence(int targetSentenceCount, const int promptMaxWordLength, bool useUniqueLines, int numberOfPassthroughs, std::vector<std::string> &fileData);

  void resetValues();

  std::vector<std::string> partitionPrompt(const std::string &prompt);

  std::string constructCurrentPrompt(std::vector<std::string> &promptVector, int promptMaxWordLength);

  std::string getRandomLine(std::vector<std::string> &fileData);

  std::string removeSpecialCharacters(const std::string &input);

  std::string getUserPrompt();

  std::string getFirstWord(const std::string &str);

  std::string getNextWord(int &foundIndex);

  std::string getCurrentPrompt();

  std::string getCurrentLine();

  void setUserPrompt();

  void setDepth(const int depth);

  int getDepth();

  void setCurrentPrompt(const std::string &prompt);

  void setCurrentLine(const std::string &line);

  std::string getFinalWord();

 private:
  int generateRandomIndex(int min, int max);
  void eraseFirstWord(std::string &str);

  int depth;
  std::string currentPrompt;
  std::string randomLine;
  std::string finalWord;
  int number_of_completed_Sentences;
  int currentIndex;  // New member variable to keep track of used line indices
};
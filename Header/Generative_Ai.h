// clang-format off
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

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class Generative_Ai {
 public:
  Generative_Ai();

  std::string generateSentence(int targetSentenceCount, const int promptMaxWordLength, bool useUniqueLines, std::vector<std::string> &fileData);

  std::vector<std::string> partitionPrompt(const std::string &prompt);

  std::string constructCurrentPrompt(std::vector<std::string> &promptVector, int promptMaxWordLength);

  std::string getRandomLine(std::vector<std::string> &fileData, bool useUniqueLines);

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
  std::set<int> usedIndices;  // New member variable to keep track of used line indices
};
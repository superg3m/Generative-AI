
#include "../Header/Generative_Ai.h"

Generative_Ai::Generative_Ai() {
  srand(time(nullptr));
  this->depth = 0;
  this->currentPrompt = "";
  this->randomLine = "";
  this->number_of_completed_Sentences = 0;
  this->currentIndex = 0;
}

std::string Generative_Ai::generateSentence(int sentenceCount, const int promptWordLength, const bool useUniqueLines, const bool useSpecialChars, int passthroughs,
                                            std::vector<std::string> &fileData) {
  if (currentPrompt.empty()) {
    this->currentPrompt = getUserPrompt();
  }
  std::string nextWord;
  int foundIndex;
  this->finalWord = currentPrompt + " ";
  std::vector<std::string> promptVector = partitionPrompt(currentPrompt);
  std::cout << "working on it...\n";
  while (this->depth < 100000000) {
    if (currentIndex == fileData.size() - 1) {
      if (passthroughs > 0) {
        passthroughs--;
        currentIndex = 0;
        File::shuffleFileData(&fileData);
      } else {
        return "\x1B[31mLines Cached Exceeds File Data Size\033[0m\t\t";
      }
    }
    if (this->number_of_completed_Sentences >= sentenceCount) {
      return "\x1B[32mSuccess\033[0m\t\t";
    }
    if (!useUniqueLines) {
      this->randomLine = getRandomLine(fileData);
    } else {
      this->randomLine = fileData.at(this->currentIndex);
      this->currentIndex++;
    }

    foundIndex = this->randomLine.find(currentPrompt);
    nextWord.clear();
    nextWord = getNextWord(foundIndex);

    if (foundIndex != std::string::npos) {
      // printf("\n");
      // std::cout << "foundIndex: " << foundIndex << "\n";
      // std::cout << "Next Word: " << nextWord << "\n";
      // std::cout << "Current Prompt: " << this->currentPrompt << "\n";
      // std::cout << "Random Line: " << this->randomLine << "\n";
    }

    if (nextWord == "FAILED") {
      this->depth++;
      continue;
    }

    if (nextWord.find('.') != std::string::npos || nextWord.find('!') != std::string::npos || nextWord.find('?') != std::string::npos) {
      // std::cout << "Sentence Completed\n";
      promptVector.clear();
      this->number_of_completed_Sentences++;
    }
    if (!useSpecialChars) {
      nextWord = removeSpecialCharacters(nextWord);
    }

    while (promptVector.size() >= promptWordLength) {
      promptVector.erase(promptVector.begin());
    }
    promptVector.push_back(nextWord);

    this->currentPrompt = constructCurrentPrompt(promptVector, promptWordLength);
    // std::cout << "new current prompt: " << this->currentPrompt << "\n";
    //  std::cout << "Next Word NOW: " << nextWord << "\n";

    this->finalWord += nextWord + " ";
    this->depth++;
    nextWord = "";
  }
  this->depth = 0;
  this->currentIndex = 0;
  return "\x1B[31mDepth Exceeded\033[0m\t\t";
}

std::string Generative_Ai::constructCurrentPrompt(const std::vector<std::string> &promptVector, const int promptMaxWordLength) const {
  std::string ret = "";

  for (int i = 0; i < promptMaxWordLength; i++) {
    if (i > promptVector.size() - 1) {
      break;
    }
    ret += promptVector.at(i) + " ";
  }

  return ret;
}

void Generative_Ai::resetValues() {
  this->depth = 0;
  this->currentPrompt = "";
  this->randomLine = "";
  this->number_of_completed_Sentences = 0;
  this->finalWord = "";
  this->currentIndex = 0;
  return;
}

std::vector<std::string> Generative_Ai::partitionPrompt(const std::string &prompt) const {
  std::vector<std::string> ret;

  std::stringstream ss(prompt);

  std::string word;

  while (ss >> word) {
    ret.push_back(word);
  }

  return ret;
}

std::string Generative_Ai::removeSpecialCharacters(const std::string &input) const {
  std::string result = "";
  for (char c : input) {
    if (c != '"' && c != '(' && c != ')' && c != '*' && c != '[' && c != ']' && c != '&' && c != '_') {  // Removing the comma is a temporary fix
      result += c;
    }
  }
  return result;
}

int Generative_Ai::generateRandomIndex(const int min, const int max) const {
  return rand() % (max - min + 1) + min;
}

std::string Generative_Ai::getRandomLine(const std::vector<std::string> &fileData) const {
  // This is the problem

  int index = generateRandomIndex(0, fileData.size() - 1);
  return fileData.at(index);
}

void Generative_Ai::eraseFirstWord(std::string &str) const {
  std::stringstream ss(str);

  std::string firstWord;

  if (ss >> firstWord) {
    str.erase(0, firstWord.length());  // Make sure this is okay
  }
}

int Generative_Ai::getDepth() const {
  return this->depth;
}

std::string Generative_Ai::getFirstWord(const std::string &str) const {
  std::stringstream ss(str);

  std::string firstWord;

  if (ss >> firstWord) {
    return firstWord;
  }

  return "FAILED";
}

std::string Generative_Ai::getNextWord(int &foundIndex) const {  // Has an critical issue where The will pick up Then and other words that contain a substring of the prompt
  std::string ret;

  if (this->randomLine.empty() || currentPrompt.empty()) {
    return "FAILED";
  }

  if (foundIndex == std::string::npos) {
    return "FAILED";
  }

  foundIndex += currentPrompt.length();

  while (foundIndex < this->randomLine.length() && this->randomLine.at(foundIndex - 1) != ' ') {
    foundIndex++;
  }

  if (foundIndex < this->randomLine.length()) {
    std::stringstream ss(this->randomLine.substr(foundIndex));

    if (ss >> ret) {
      return ret;
    }
  }

  return "FAILED";
}

std::string Generative_Ai::getCurrentPrompt() const {
  return this->currentPrompt;
}

std::string Generative_Ai::getCurrentLine() const {
  return this->randomLine;
}

std::string Generative_Ai::getUserPrompt() const {
  std::string prompt;

  std::cout << "Enter a prompt: ";
  std::getline(std::cin, prompt);
  printf("\n");
  return prompt;
}

std::string Generative_Ai::getFinalWord() {
  return this->finalWord;
}

void Generative_Ai::setUserPrompt() {
  this->currentPrompt = getUserPrompt();
}

void Generative_Ai::setDepth(int depth) {
  this->depth = depth;
}

void Generative_Ai::setCurrentPrompt(const std::string &prompt) {
  this->currentPrompt = prompt;
}

void Generative_Ai::setCurrentLine(const std::string &line) {
  this->randomLine = line;
}
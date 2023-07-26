
#include "../Header/Generative_Ai.h"

Generative_Ai::Generative_Ai() {
  srand(time(nullptr));
  this->depth = 0;
  this->currentPrompt = "";
  this->randomLine = "";
  this->number_of_completed_Sentences = 0;
}

std::string Generative_Ai::generateSentence(int targetSentenceCount, const int promptMaxWordLength, bool useUniqueLines, int numberOfPassthroughs, std::vector<std::string> &fileData) {
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
      if (numberOfPassthroughs > 0) {
        numberOfPassthroughs--;
        currentIndex = 0;
        File::shuffleFileData(&fileData);
      } else {
        return "All lines used";
      }
    }
    if (this->number_of_completed_Sentences >= targetSentenceCount) {
      return "Success";
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

    nextWord = removeSpecialCharacters(nextWord);
    if (promptVector.size() == promptMaxWordLength) {
      promptVector.erase(promptVector.begin());
    }

    promptVector.push_back(nextWord);

    this->currentPrompt = constructCurrentPrompt(promptVector, promptMaxWordLength);
    // std::cout << "new current prompt: " << this->currentPrompt << "\n";
    this->finalWord += nextWord + " ";
    // std::cout << "Final Word: " << this->finalWord << "\n";
    this->depth++;
    nextWord = "";
  }
  this->depth = 0;
  this->currentIndex = 0;
  return "Depth Exceeded";
}

std::string Generative_Ai::constructCurrentPrompt(std::vector<std::string> &promptVector, int promptMaxWordLength) {
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

std::vector<std::string> Generative_Ai::partitionPrompt(const std::string &prompt) {
  std::vector<std::string> ret;

  std::stringstream ss(prompt);

  std::string word;

  while (ss >> word) {
    ret.push_back(word);
  }

  return ret;
}

std::string Generative_Ai::removeSpecialCharacters(const std::string &input) {
  std::string result = "";
  for (char c : input) {
    if (c != '"' && c != '(' && c != ')' && c != '*' && c != ',' && c != '[' && c != ']') {  // Removing the comma is a temporary fix
      result += c;
    }
  }
  return result;
}

int Generative_Ai::generateRandomIndex(const int min, const int max) {
  return rand() % (max - min + 1) + min;
}

std::string Generative_Ai::getRandomLine(std::vector<std::string> &fileData) {
  // This is the problem

  int index = generateRandomIndex(0, fileData.size() - 1);
  return fileData.at(index);
}

void Generative_Ai::eraseFirstWord(std::string &str) {
  std::stringstream ss(str);

  std::string firstWord;

  if (ss >> firstWord) {
    str.erase(0, firstWord.length());  // Make sure this is okay
  }
}

int Generative_Ai::getDepth() {
  return this->depth;
}

std::string Generative_Ai::getFirstWord(const std::string &str) {
  std::stringstream ss(str);

  std::string firstWord;

  if (ss >> firstWord) {
    return firstWord;
  }

  return "FAILED";
}

std::string Generative_Ai::getNextWord(int &foundIndex) {  // Has an critical issue where The will pick up Then and other words that contain a substring of the prompt
  std::string ret;

  if (this->randomLine.empty() || currentPrompt.empty()) {
    std::cout << "FUCK\n";
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

std::string Generative_Ai::getCurrentPrompt() {
  return this->currentPrompt;
}

std::string Generative_Ai::getCurrentLine() {
  return this->randomLine;
}

void Generative_Ai::setUserPrompt() {
  this->currentPrompt = getUserPrompt();
}

std::string Generative_Ai::getUserPrompt() {
  std::string prompt;

  std::cout << "Enter a prompt: ";
  std::getline(std::cin, prompt);
  printf("\n");
  return prompt;
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

std::string Generative_Ai::getFinalWord() {
  return this->finalWord;
}
#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// Look to see if Generators are viable
// TODO make this multi Threaded
// TODO Atomic hash table

#include "../Header/File.h"
#include "../Header/Generative_Ai.h"

int main() {
  const char* python_script = "python ../PythonScripts/FormatTxtFiles.py";

  // Run the Python script using the Python interpreter
  int exit_code = std::system(python_script);

  // Check the exit code to see if the Python script ran successfully
  if (exit_code == 0) {
    std::cout << "Python script executed successfully." << std::endl;
  } else {
    std::cerr << "Error executing Python script." << std::endl;
  }

  std::vector<std::string> fileData;
  File file(&fileData);
  // file.addFileData("../FileOutput/Frankenstein.txt");
  file.loadALlFilesInDirectory("../FileOutput");

  std::cout << "SIZE: " << fileData.size() << "\n";

  int success;

  int total = 10;
  int sentenceCount = 1;
  int promptWordLength = 3;
  bool useUniqueLines = true;
  bool usePunctuation = true;
  int numberOfPassthroughs = 25;

  float successRate;

  Generative_Ai generativeAi;
  std::string input;
  std::cout << "Enter a prompt: ";
  std::getline(std::cin, input);
  file.shuffleFileData(&fileData);
  for (int i = 0; i < total; i++) {
    generativeAi.setCurrentPrompt(input);
    std::string finalSentence = generativeAi.generateSentence(sentenceCount, promptWordLength, useUniqueLines, usePunctuation, numberOfPassthroughs, fileData);
    if (finalSentence == "Depth Exceeded") {
      std::cout << "\x1B[31mDepth Exceeded\033[0m\t\t\n";
    } else if (finalSentence == "All lines used") {
      std::cout << "\x1B[31mLines Cached Exeeds File data size\033[0m\t\t\n";
    } else if (finalSentence == "Success") {
      std::cout << "\x1B[32mSuccess\033[0m\t\t\n";
      success++;
    }
    std::cout << "#" << i + 1 << " | The Prompt: " << generativeAi.getCurrentPrompt() << "\n";
    std::cout << "#" << i + 1 << " | The Final Sentence: " << generativeAi.getFinalWord() << "\n";
    printf("\n");
    file.shuffleFileData(&fileData);
    generativeAi.resetValues();
  }
  successRate = static_cast<float>(success) / total;

  std::cout << "The success rate: \x1B[34m" << successRate << "\033[0m\t\t"
            << "\n";
  return 0;
}
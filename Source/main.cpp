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

// TODO take the available indexs and then randomize from that
// TODO improve the algorithm to increase speed
// TODO randomize the data somehow and have incremental access of the data
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

  file.loadALlFilesInDirectory("../FileOutput");

  std::cout << "SIZE: " << fileData.size() << "\n";

  Generative_Ai generativeAi;

  std::string finalSentence = generativeAi.generateSentence(1, 2, false, fileData);

  if (finalSentence == "Depth Exceeded") {
    std::cout << "\x1B[31mDepth Exceeded\033[0m\t\t\n";
  } else if (finalSentence == "All lines used") {
    std::cout << "\x1B[31mLines Cached Exeeds File data size\033[0m\t\t\n";
  }

  // Chec,;
  std::cout << "The Final Sentence: " << generativeAi.getFinalWord() << "\n";
  return 0;
}
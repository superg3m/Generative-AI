#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class File {
 public:
  File(std::vector<std::string>* fileData);

  void addFileData(const std::string& fileName);

  void loadALlFilesInDirectory(const std::string& directory);

  static void shuffleFileData(std::vector<std::string>* fileData) {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(fileData->begin(), fileData->end(), rng);
  }

 private:
  std::string removeSmartCharacters(const std::string& input) const;

  void format_and_save_text_data(const std::string& fileName);

  std::vector<std::string>* fileData;
};

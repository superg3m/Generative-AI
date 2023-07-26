#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class File {
 public:
  File(std::vector<std::string>* textData);

  void addFileData(const std::string& fileName);

  void loadALlFilesInDirectory(const std::string& directory);

 private:
  std::string removeSmartCharacters(const std::string& input);

  void format_and_save_text_data(const std::string& fileName);

  std::vector<std::string>* textData;
};

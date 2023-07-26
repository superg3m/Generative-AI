#include "../Header/File.h"

File::File(std::vector<std::string>* fileData) {
  this->fileData = fileData;
}

void File::addFileData(const std::string& fileName) {
  format_and_save_text_data(fileName);
}

void File::loadALlFilesInDirectory(const std::string& directory) {
  fs::path directory_path = directory;

  if (fs::exists(directory_path) && fs::is_directory(directory_path)) {
    for (const auto& entry : fs::directory_iterator(directory_path)) {
      if (fs::is_regular_file(entry)) {
        fs::path relative_path = fs::relative(entry.path(), directory_path);
        this->addFileData(directory + "/" + relative_path.string());
      }
    }
  } else {
    std::cerr << "Invalid directory path or directory does not exist." << std::endl;
  }
}

std::string File::removeSmartCharacters(const std::string& input) {  // Doesn't work at all for some reason
  std::string result;
  for (char c : input) {
    if (c == '’') {  // Smart single quote
      result += "'";
    } else if (c == '–') {  // Smart hyphen
      result += "-";
    } else if (c == '”') {
      std::cout << "Found a smart double quote end" << std::endl;
      result += '"';
    } else if (c == '“') {
      std::cout << "Found a smart double quote beginning" << std::endl;
      result += '"';
    } else if (c == '…') {
      result += "...";
    } else {
      result += c;
    }
  }
  return result;
}

void File::format_and_save_text_data(const std::string& fileName) {
  std::ifstream file(fileName);
  std::string line;
  if (!file.is_open()) {
    std::cerr << "\x1B[31mThe file failed to open: \033[0m\t\t"
              << "\x1B[35m" << fileName << "\033[0m\t\t" << std::endl;
    exit(1);
  }
  while (std::getline(file, line)) {
    line = removeSmartCharacters(line);  // Doesn't work at all for some reason
    if (!line.empty()) {
      this->fileData->push_back(line);
    }
  }

  file.close();
}